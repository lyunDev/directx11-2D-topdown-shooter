#include "Framework.h"
#include "AnimationRect.h"
#include "Utilities/Animator.h"

AnimationRect::AnimationRect(Transform * transform)
	: IntegratedRect(transform)
{
	{
		D3D11_SAMPLER_DESC desc;
		States::GetSamplerDesc(&desc);
		States::CreateSampler(&desc, &point[0]);

		desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		States::CreateSampler(&desc, &point[1]);
	}

	{
		D3D11_BLEND_DESC desc;
		States::GetBlendDesc(&desc);
		States::CreateBlend(&desc, &blend[0]);

		desc.RenderTarget[0].BlendEnable = true;
		States::CreateBlend(&desc, &blend[1]);
	}

	animator = new Animator();
}

AnimationRect::~AnimationRect()
{
	SAFE_RELEASE(point[0]);
	SAFE_RELEASE(point[1]);
}

void AnimationRect::Update()
{
	SetSRV(animator->GetCurrentSRV());
	animator->Update();

	{
		MapVertexBuffer();
		{
			vertices[0].uv =
				Vector2
				(
					animator->GetCurrentFrame().x,
					animator->GetCurrentFrame().y + animator->GetTexelFrameSize().y
				);
			vertices[1].uv = animator->GetCurrentFrame();
			vertices[2].uv = animator->GetCurrentFrame() + animator->GetTexelFrameSize();
			vertices[3].uv =
				Vector2
				(
					animator->GetCurrentFrame().x + animator->GetTexelFrameSize().x,
					animator->GetCurrentFrame().y
				);

			
		}
		UnmapVertexBuffer();


		UpdateWorld();
	}

}

void AnimationRect::Render()
{
	

	//DC->PSSetSamplers(0, 1, &point[1]); // sampler point
	//DC->OMSetBlendState(blend[1], nullptr, 0xffffffff);
	IntegratedRect::Render();
	//DC->OMSetBlendState(blend[0], nullptr, 0xffffffff);
	//DC->PSSetSamplers(0, 1, &point[0]); // sampler linear
	
}
