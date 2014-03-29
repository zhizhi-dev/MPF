#pragma once
#include "../Type.h"

NS_MPF
NS_VSL

//图片
class Image : public Object
{
public:
	//创建 Image 的新实例
	MPF_API Image(std::istream& stream);
	//创建 Image 的新实例
	MPF_API Image(const std::vector<byte>& data);

	//获取类型
	MPF_API DECLARE_GETTYPE(Image)
	MPF_API DECLARE_GETINSTANTTYPE(Image)
private:
	DECLARE_TYPE(Image)
};

NS_ED
NS_ED