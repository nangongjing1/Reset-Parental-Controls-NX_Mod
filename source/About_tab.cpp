#include "about_tab.hpp"

AboutTab::AboutTab() {
	brls::Label* Label1 = new brls::Label(brls::LabelStyle::REGULAR, "重置家长控制 1.2.0", false);
	this->addView(Label1);

	brls::Label* Label2 = new brls::Label(brls::LabelStyle::MEDIUM, "研发: TotalJustice\nBorealis UI 重制: MasaGratoR\n中文翻译: 南宫镜", true);
	this->addView(Label2);
	
	brls::Label* Label3 = new brls::Label(brls::LabelStyle::DESCRIPTION, "Copyright (C) 2020 - 2025\n本程序为开源软件: 您可依据自由软件基金会发布的《GNU 通用公共许可证》第 3 版的条款, 重新分发和/或修改本程序. 本程序的分发旨在提供实用价值, 但不附带任何担保; 既不包含明示担保, 也不包含适销性或特定用途适用性的默示担保. 有关更多细节, 请参阅《GNU 通用公共许可证》. 您应已随本程序一同收到《GNU 通用公共许可证》的副本; 若未收到, 请访问 https://www.gnu.org/licenses/", true);
	this->addView(Label3);
}