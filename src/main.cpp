#include "events.h"
#include "hooks.h"
#include "payloadManager.h"
void MessageHandler(SKSE::MessagingInterface::Message* a_msg)
{
	switch (a_msg->type) {
	case SKSE::MessagingInterface::kDataLoaded:
		//dataHandler::testInsertWeaponArt();
		//((animEventHandler*)((uintptr_t)RE::PlayerCharacter::GetSingleton() + 0x30))->HookSink();
		INFO("Hooksink anim events...");
		REL::Relocation<uintptr_t> npcPtr{ REL::ID(261399) };
		REL::Relocation<uintptr_t> pcPtr{ REL::ID(261918) };
		animEventHandler::HookSink(pcPtr.address());
		animEventHandler::HookSink(npcPtr.address());
		INFO("Anim event hook sinked");
		payloadManager::loadPreDefinedPayload();
		break;
	}
}

//extern "C" DLLEXPORT bool SKSEAPI SKSEPlugin_Query(const SKSE::QueryInterface* a_skse, SKSE::PluginInfo* a_info)
//{
//	DKUtil::Logger::Init(Plugin::NAME, Plugin::STRINGVERSION);
//
//	a_info->infoVersion = SKSE::PluginInfo::kVersion;
//	a_info->name = Plugin::NAME.data();
//	a_info->version = Plugin::Version[0];
//
//	if (a_skse->IsEditor()) {
//		ERROR("Loaded in editor, marking as incompatible"sv);
//		return false;
//	}
//
//	const auto ver = a_skse->RuntimeVersion();
//	if (ver < SKSE::RUNTIME_1_5_39) {
//		ERROR("Unable to load this plugin, incompatible runtime version!\nExpected: Newer than 1-5-39-0 (A.K.A Special Edition)\nDetected: {}", ver.string());
//		return false;
//	}
//
//	return true;
//}


DLLEXPORT bool SKSEAPI SKSEPlugin_Load(const SKSE::LoadInterface* a_skse)
{
#ifndef NDEBUG
	while (!IsDebuggerPresent()) { Sleep(100); }
#endif

	INFO("{} v{} loaded", Plugin::NAME, Plugin::STRINGVERSION);

	SKSE::Init(a_skse);
	auto messaging = SKSE::GetMessagingInterface();
	if (!messaging->RegisterListener("SKSE", MessageHandler)) {
		return false;
	}
	Hooks::install();
	return true;
}
