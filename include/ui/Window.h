#pragma once
#include "ContentElement.h"
#include "../visual/RenderCoreProviders.h"

NS_MPF
NS_VSL
class NativeWindow;
NS_ED

NS_UI

//窗口
class Window : public ContentElement
{
public:
	//创建 Brush 的新实例
	MPF_API Window();
	MPF_API virtual ~Window();

	//加载
	MPF_API virtual void Initialize(MPF::Visual::RenderCoreProviders provider = 
		MPF::Visual::RenderCoreProviders::GDI);

	//获取标题
	MPF_API const MPF::String& GetTitle() const;
	//设置标题
	MPF_API void SetTitle(const MPF::String& value);
	//设置标题
	MPF_API void SetTitle(MPF::String&& value);
	//获取或设置标题
	mproperty(MPF::String, Title);

	//显示
	MPF_API void Show();

	//绘制帧
	MPF_API void DoFrame();

	//获取类型
	MPF_API DECLARE_GETTYPE(Window);
	MPF_API DECLARE_GETINSTANTTYPE(Window);
	DECLARE_PUB_UI_FUNCS;
public:
	//标题
	MPF_API static DependencyProperty<MPF::String> TitleProperty;
protected:
	//更新相对父节点的偏移
	MPF_API virtual void UpdateRelativeOffset() mnoexcept;
	DECLARE_UI_FUNCS
private:
	void InitializeNativeWindowEventHandlers();
private:
	std::unique_ptr<MPF::Visual::NativeWindow> nativeWindow;
	std::unique_ptr<MPF::Visual::RenderCoreProvider> renderer;
	DECLARE_UI_VALUES
	DECLARE_TYPE(Window)
};

NS_ED
NS_ED