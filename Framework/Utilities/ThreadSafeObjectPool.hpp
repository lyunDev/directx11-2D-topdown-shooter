
#ifndef OBJECTPOOL_H
#define OBJECTPOOL_H



#include <memory>
#include <vector>
#include <condition_variable>
#include <mutex>

	using std::unique_ptr;
	using std::weak_ptr;
	using std::shared_ptr;
	using std::vector;
	using std::condition_variable;
	using std::mutex;
	using std::unique_lock;
	using std::conditional;
	using std::remove_reference;
	using std::is_reference;


	template<typename type>
	class DefaultFactory
	{
	public:
		type *create()
		{
			return new type();
		}
	};

	/**
	 * Common Object Pool
	 * if factory_type is not given, use default factory
	 * @tparam type object type
	 * @tparam factory_type factory type
	 */
	template<typename type, class factory_type = DefaultFactory<type>>
	class ThreadSafeObjectPool : public std::enable_shared_from_this<ThreadSafeObjectPool<type, factory_type>>
	{
	private:
		class return_to_pool;

		using pool_type = ThreadSafeObjectPool<type, factory_type>;
		using deleter_type = pool_type::return_to_pool;
		using ptr_type = unique_ptr<type>;
	public:
		using return_ptr_type = unique_ptr<type, deleter_type>;

		explicit ThreadSafeObjectPool(std::size_t _init_size)
			: max_size(2 * init_size),
			current_size(0),
			init_size(_init_size)
		{
			init();
		}

		ThreadSafeObjectPool(std::size_t _init_size, typename remove_reference<factory_type>::type &&factory)
			: max_size(2 * _init_size),
			current_size(0),
			init_size(_init_size),
			factory(std::move(factory))
		{
			init();
		}

		ThreadSafeObjectPool(std::size_t _init_size,
			typename conditional<is_reference<factory_type>::value, factory_type, const factory_type &>::type factory)
			: max_size(2 * _init_size),
			current_size(0),
			init_size(_init_size)
		{
			this->factory = factory;
			init();
		}

		/**
		 * return a object to pool
		 * @param object smart pointer contain object
		 */
		void release(ptr_type &object)
		{
			unique_lock<mutex> lck(this->object_mutex);
			this->objects.push_back(move(object));
			// notify a random thread
			idle_cv.notify_one();
		}

		/**
		 * borrow a object from pool
		 * object will be returned automatically when smart pointer deconstruct
		 * so don't call smart pointer release() or move it to other smart pointer
		 * @return smart pointer managed object
		 */
		return_ptr_type acquire()
		{
			unique_lock<mutex> lck(this->object_mutex);

			while (true)
			{
				auto size = this->objects.size();

				if (size > 0)
				{
					return_ptr_type ptr(this->objects.back().release(), deleter_type{ this->shared_from_this() });
					this->objects.pop_back();
					return ptr;
				}
				else
				{
					// try to create a new object if not full
					auto obj = this->create_object();
					if (obj != nullptr)
						return return_ptr_type(obj, deleter_type{ this->shared_from_this() });
					// pool is full, just wait other thread release
					idle_cv.wait(lck);
				}
			}
		}

	private:
		std::size_t current_size;
		std::size_t max_size;
		std::size_t init_size;

		mutex object_mutex;
		condition_variable idle_cv;

		factory_type factory;
		vector<unique_ptr<type>> objects;

		/**
		 * call factory to create a new object
		 * @return
		 */
		inline type *create_object()
		{
			if (current_size < max_size)
			{
				this->current_size++;
				return factory.create();
			}
			else return nullptr;
		}

		inline void init()
		{
			for (int i = 0; i < init_size; ++i)
				this->objects.emplace_back(this->create_object());
		}

		/**
		 * custom deleter
		 * return object to pool when called
		 */
		class return_to_pool
		{
		private:
			weak_ptr<pool_type> pool;
		public:
			explicit return_to_pool(const shared_ptr<pool_type> &ptr) : pool(ptr)
			{}

			void operator()(type *object)
			{
				// if pool was free, make sure to delete object
				ptr_type ptr(object);
				if (auto sp = this->pool.lock())
				{
					try
					{
						sp->release(ptr);
					}
					catch (...)
					{
					}
				}
			}
		};
	};

#endif //OBJECTPOOL_H