#pragma once
#include "Brush.h"
#include "BitmapData.h"

NS_MPF
NS_VSL

//Alpha混合画刷
class AlphaBlendBrush : public Brush
{
public:
	//创建 AlphaBlendBrush 的新实例
	MPF_API AlphaBlendBrush(const BitmapData<byte>& alpha, 
		const Brush& secondBrush) mnoexcept;

	//采样
	MPF_API virtual color_t TakeSample(float u, float v) const;

	//获取 Alpha 数据
	MPF_API const BitmapData<byte>& GetAlpha() const mnoexcept;
	//设置 Alpha 数据
	MPF_API void SetAlpha(const BitmapData<byte>& value) mnoexcept;
	//获取或设置 Alpha 数据
	mproperty(const BitmapData<byte>&, Alpha);

	//获取第二 Brush
	MPF_API const Brush& GetSecondBrush() const mnoexcept;
	//设置第二 Brush
	MPF_API void SetSecondBrush(const Brush& value) mnoexcept;
	//获取或设置第二 Brush
	mproperty(const Brush&, SecondBrush)

	//获取类型
	MPF_API DECLARE_GETTYPE(AlphaBlendBrush);
	MPF_API DECLARE_GETINSTANTTYPE(AlphaBlendBrush);
private:
	const BitmapData<byte>* alpha;
	const Brush* secondBrush;

	DECLARE_TYPE(AlphaBlendBrush)
};

NS_ED
NS_ED