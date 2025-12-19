#include <switch.h>

#include <borealis.hpp>

#include "About_tab.hpp"

// works
Result pctlDeleteParentalControls(void)
{
	return serviceDispatch(pctlGetServiceSession_Service(), 1043);
}

// works
Result pctlDeletePairing(void)
{
	return serviceDispatch(pctlGetServiceSession_Service(), 1941);
}

int main(int argc, char *argv[])
{
	// Init the app

	if (!brls::Application::init("重置家长控制"))
	{
		brls::Logger::error("初始化重置家长控制失败");
		return EXIT_FAILURE;
	}

	// 尝试加载中文字体
#ifdef __SWITCH__
	PlFontData font;
	Result rc = plGetSharedFontByType(&font, PlSharedFontType_ChineseSimplified);
	if (R_SUCCEEDED(rc))
	{
		brls::Logger::info("Adding Chinese simplified font");
		int chineseFont = brls::Application::loadFontFromMemory("chinese", font.address, font.size, false);
		nvgAddFallbackFontId(brls::Application::getNVGContext(), brls::Application::getFontStash()->regular, chineseFont);
	}
#endif

	// Create a sample view
	pctlInitialize();
	brls::TabFrame* rootFrame = new brls::TabFrame();
	rootFrame->setTitle("重置家长控制");
	rootFrame->setIcon(BOREALIS_ASSET("icon.jpg"));
	
	brls::List* OptionsList = new brls::List();

	brls::ListItem* RegisterPasscode = new brls::ListItem("设置家长控制 PIN");
	RegisterPasscode->getClickEvent()->subscribe([](brls::View* view) {
		pctlExit();
		if (R_FAILED(pctlauthRegisterPasscode())) {
			std::string notification = "进程已取消.";
			brls::Application::notify(notification);
		}
		else {
			std::string notification = "PIN 设置成功!";
			brls::Application::notify(notification);
		}
		pctlInitialize();
	});
	
	OptionsList->addView(RegisterPasscode);
	
	brls::ListItem* DeleteParentalControls = new brls::ListItem("移除家长控制");
	DeleteParentalControls->getClickEvent()->subscribe([](brls::View* view) {
		bool isRestricted = false;
		pctlIsRestrictionEnabled(&isRestricted);
		if (isRestricted == true) {
			if (R_FAILED(pctlDeleteParentalControls())) {
				std::string notification = "进程已取消.";
				brls::Application::notify(notification);
			}
			else {
				std::string notification = "成功移除家长控制.";
				brls::Application::notify(notification);
			}
		}
		else {
		 std::string notification = "家长控制已被禁用.";
		 brls::Application::notify(notification);
		}
	});
	
	OptionsList->addView(DeleteParentalControls);
	
	brls::ListItem* DeletePairing = new brls::ListItem("移除家长控制 App 配对");
	DeletePairing->getClickEvent()->subscribe([](brls::View* view) {
		Result rc = pctlDeletePairing();
		if (R_FAILED(rc)) {
			std::string notification = "进程已取消.";
			brls::Application::notify(notification);
		}
		else {
			std::string notification = "成功移除家长控制 App 配对.";
			brls::Application::notify(notification);
		}
	});
	
	OptionsList->addView(DeletePairing);
	
	rootFrame->addTab("主要选项", OptionsList);
	
	rootFrame->addTab("关于软件", new AboutTab());


	// Add the root view to the stack
	brls::Application::pushView(rootFrame);

	// Run the app
	while (brls::Application::mainLoop());

	// Exit
	pctlExit();
	return EXIT_SUCCESS;
}