#pragma once


class AnimationClip
{
public:
	AnimationClip
	(
		wstring clipName,
		Texture2D* srcTex,
		uint frameCount,
		Vector2 startPos,
		Vector2 endPos,
		float playRate,
		bool bReversed = false
	);
	AnimationClip
	(
		wstring clipName,
		Texture2D* srcTex,
		uint frameXCount,
		uint frameYCount,
		Vector2 startPos,
		Vector2 endPos,
		float playRate,
		bool bReversed = false
	);

private:

	wstring clipName = L"";
	vector<Vector2> keyframes;
	uint frameCount = 0;
	uint frameXCount = 0;
	uint frameYCount = 0;
	ID3D11ShaderResourceView * srv = nullptr;
	Vector2 texelFrameSize = Values::ZeroVec2;
	float playRate = 0.0f; // 1.0f / 15.0f

	bool bReversed = false;

	friend class Animator;
};

class Animator
{
public :
	Animator();
	~Animator();

	void Update();
	Vector2 GetCurrentFrame() { return currentFrame; }
	Vector2 GetTexelFrameSize() { return currentClip->texelFrameSize; }
	ID3D11ShaderResourceView* GetCurrentSRV() { return currentClip->srv; }

	void AddAnimClip(AnimationClip* animClip);
	void SetCurrentAnimClip(wstring clipName);

	void SetIdleClip(AnimationClip* clip)
	{
		idle = clip;

		AddAnimClip(clip);
	}

	void SetMoveRightClip(AnimationClip* clip)
	{
		moveRight = clip;

		AddAnimClip(clip);
	}
	void SetMoveLeftClip(AnimationClip* clip)
	{
		moveLeft = clip;

		AddAnimClip(clip);
	}
	void SetMoveUpClip(AnimationClip* clip)
	{
		moveUp = clip;

		AddAnimClip(clip);
	}
	void SetMoveDownClip(AnimationClip* clip)
	{
		moveDown = clip;

		AddAnimClip(clip);
	}
	void SetActionClip(AnimationClip* clip)
	{
		action = clip;

		AddAnimClip(clip);
	}

	void PlayIdle() { SetCurrentAnimClip(idle->clipName); }
	void PlayMoveLeft() { SetCurrentAnimClip(moveLeft->clipName); }
	void PlayMoveRight() { SetCurrentAnimClip(moveRight->clipName); }
	void PlayMoveUp() { SetCurrentAnimClip(moveUp->clipName); }
	void PlayMoveDown() { SetCurrentAnimClip(moveDown->clipName); }
	void PlayAction() { SetCurrentAnimClip(action->clipName); }

	void AnimStart()
	{
		bAnimStop = false;
	}
	void AnimStop()
	{
		bAnimStop = true;
	}
	void AnimRestart()
	{
		bAnimStop = false;
		
		if (currentClip != nullptr && currentClip->bReversed == false)
			currentFrameIndex = 0;
		else if (currentClip != nullptr)
			currentFrameIndex = currentClip->frameCount - 1;

	}
	
private:
	bool CheckExist(wstring clipName)
	{
		return animClips.find(clipName) != animClips.end();
	}
private :

	unordered_map<wstring, AnimationClip *> animClips;

	AnimationClip* currentClip = nullptr;
	uint currentFrameIndex = 0;
	Vector2 currentFrame = Values::ZeroVec2;

	float deltaTime = 0.0f;
	bool bAnimStop = false;

	AnimationClip* idle = nullptr;
	AnimationClip* moveLeft = nullptr;
	AnimationClip* moveRight = nullptr;
	AnimationClip* moveUp = nullptr;
	AnimationClip* moveDown = nullptr;
	AnimationClip* action = nullptr;

public :
	function<void(void)> onAnimationFinished = {NULL};
};