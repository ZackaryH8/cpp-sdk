#pragma once

#include <climits>

#include "deps/alt-math/alt-math.h"
#include "deps/alt-config/alt-config.h"
#include "types/RGBA.h"
#include "types/Array.h"
#include "types/MValue.h"
#include "types/StringView.h"
#include "Ref.h"

#include "events/CEvent.h"
#include "IResource.h"
#include "IPackage.h"
#include "IDiscordManager.h"

#include "objects/ILocalPlayer.h"

#include "script-objects/IBlip.h"
#include "script-objects/ICheckpoint.h"
#include "script-objects/IColShape.h"
#include "script-objects/IWebView.h"
#include "script-objects/IStatData.h"
#include "script-objects/IHandlingData.h"
#include "script-objects/INative.h"
#include "script-objects/IMapData.h"
#include "script-objects/IHttpClient.h"
#include "script-objects/IAudio.h"
#include "script-objects/IRml.h"

#include "types/KeyState.h"
#include "types/Permissions.h"
#include "types/VehicleModelInfo.h"

namespace alt
{
	class IEntity;
	class IPlayer;
	class IVehicle;
	class ICheckpoint;
	class IScriptRuntime;
	class IVoiceChannel;
	class ILocalPlayer;

	using CommandCallback = std::function<void(const std::vector<std::string>& args)>;

	static constexpr int32_t DEFAULT_DIMENSION = 0;
	static constexpr int32_t GLOBAL_DIMENSION = INT_MIN;

	class ICore
	{
	public:
		// Shared methods
		virtual std::string GetVersion() const = 0;
		virtual std::string GetBranch() const = 0;

		virtual void LogInfo(StringView str) = 0;
		virtual void LogDebug(StringView str) = 0;
		virtual void LogWarning(StringView str) = 0;
		virtual void LogError(StringView str) = 0;
		virtual void LogColored(StringView str) = 0;

		virtual MValueNone CreateMValueNone() = 0;
		virtual MValueNil CreateMValueNil() = 0;
		virtual MValueBool CreateMValueBool(bool val) = 0;
		virtual MValueInt CreateMValueInt(int64_t val) = 0;
		virtual MValueUInt CreateMValueUInt(uint64_t val) = 0;
		virtual MValueDouble CreateMValueDouble(double val) = 0;
		virtual MValueString CreateMValueString(String val) = 0;
		virtual MValueList CreateMValueList(Size size = 0) = 0;
		virtual MValueDict CreateMValueDict() = 0;
		virtual MValueBaseObject CreateMValueBaseObject(Ref<IBaseObject> val) = 0;
		virtual MValueFunction CreateMValueFunction(IMValueFunction::Impl *impl) = 0;
		virtual MValueVector2 CreateMValueVector2(Vector2f val) = 0;
		virtual MValueVector3 CreateMValueVector3(Vector3f val) = 0;
		virtual MValueRGBA CreateMValueRGBA(RGBA val) = 0;
		virtual MValueByteArray CreateMValueByteArray(const uint8_t *data, Size size) = 0;
		virtual MValueByteArray CreateMValueByteArray(Size size) = 0;

		virtual bool IsDebug() const = 0;

		virtual uint32_t Hash(StringView str) const = 0;

		virtual bool RegisterScriptRuntime(StringView resourceType, IScriptRuntime *runtime) = 0;

		virtual bool SubscribeCommand(const std::string& cmd, CommandCallback cb) = 0;

		virtual bool FileExists(StringView path) = 0;
		virtual String FileRead(StringView path) = 0;

		virtual IResource *GetResource(StringView name) = 0;

		virtual Ref<IEntity> GetEntityByID(uint16_t id) const = 0;

		virtual Array<Ref<IEntity>> GetEntities() const = 0;
		virtual Array<Ref<IPlayer>> GetPlayers() const = 0;
		virtual Array<Ref<IVehicle>> GetVehicles() const = 0;
		virtual Array<Ref<IBlip>> GetBlips() const = 0;

		virtual void TriggerLocalEvent(StringView ev, MValueArgs args) = 0;

		virtual bool HasMetaData(const std::string& key) const = 0;
		virtual MValueConst GetMetaData(const std::string& key) const = 0;
		virtual void SetMetaData(const std::string& key, MValue val) = 0;
		virtual void DeleteMetaData(const std::string& key) = 0;

		virtual bool HasSyncedMetaData(const std::string& key) const = 0;
		virtual MValueConst GetSyncedMetaData(const std::string& key) const = 0;

		virtual const Array<Permission> GetRequiredPermissions() const = 0;
		virtual const Array<Permission> GetOptionalPermissions() const = 0;

        virtual alt::IPackage::PathInfo Resolve(IResource *resource, StringView path, StringView currentModulePath) const = 0;

		virtual void DestroyBaseObject(Ref<IBaseObject> handle) = 0;

		virtual const std::vector<IResource*> GetAllResources() const = 0;

#ifdef ALT_CLIENT_API // Client methods
		virtual IDiscordManager *GetDiscordManager() const = 0;
		virtual IStatData *GetStatData(StringView statname) const = 0;
		virtual alt::Ref<alt::IHandlingData> GetHandlingData(uint32_t modelHash) const = 0;

		virtual void TriggerServerEvent(StringView ev, MValueArgs args) = 0;

		virtual Ref<ILocalPlayer> GetLocalPlayer() const = 0;

		virtual bool IsSandbox() const = 0;
		virtual KeyState GetKeyState(uint32_t keyCode) const = 0;
		virtual bool AreControlsEnabled() const = 0;
		virtual Vector2f GetCursorPosition(bool normalized = false) const = 0;
		virtual void SetCursorPosition(Vector2f pos, bool normalized = false) = 0;

		virtual bool SetConfigFlag(StringView flag, bool state) = 0;
		virtual bool GetConfigFlag(StringView flag) const = 0;
		virtual bool DoesConfigFlagExist(StringView flag) const = 0;

		virtual void SetVoiceInputMuted(bool state) = 0;
		virtual bool IsVoiceInputMuted() const = 0;
		virtual bool IsVoiceActivationEnabled() const = 0;
		virtual void ToggleVoiceControls(bool state) = 0;
		virtual uint32_t GetVoiceActivationKey() = 0;

		virtual String GetLicenseHash() const = 0;
		virtual String GetLocale() const = 0;
		virtual bool IsInStreamerMode() const = 0;
		virtual bool IsMenuOpen() const = 0;
		virtual bool IsConsoleOpen() const = 0;

		virtual const Array<INative *> GetAllNatives() const = 0;
		virtual Ref<INative::Context> CreateNativesContext() const = 0;

		virtual Ref<IEntity> GetEntityByScriptGuid(int32_t scriptGuid) const = 0;

		virtual void *GetTextureFromDrawable(uint32_t modelHash, StringView targetTextureName) const = 0;

		virtual void RequestIPL(StringView ipl) = 0;
		virtual void RemoveIPL(StringView ipl) = 0;

		virtual bool BeginScaleformMovieMethodMinimap(StringView methodName) = 0;

		virtual int32_t GetMsPerGameMinute() const = 0;
		virtual void SetMsPerGameMinute(int32_t val) = 0;
		virtual void SetWeatherCycle(alt::Array<uint8_t> weathers, alt::Array<uint8_t> multipliers) = 0;
		virtual void SetWeatherSyncActive(bool active) = 0;

		virtual void SetCamFrozen(bool frozen) = 0;
		virtual bool IsCamFrozen() = 0;

		virtual alt::Ref<alt::IMapData> GetMapData(uint8_t zoomDataId) = 0;
		virtual alt::Ref<alt::IMapData> GetMapData(StringView alias) = 0;
		virtual uint8_t GetMapDataIDFromAlias(StringView alias) = 0;
		virtual void ResetMapData(uint8_t zoomDataId) = 0;
		virtual void ResetMapData(StringView alias) = 0;
		virtual void ResetAllMapData() = 0;

		virtual PermissionState GetPermissionState(Permission permission) const = 0;

		using TakeScreenshotCallback = std::function<void(StringView base64)>;
		/**
		 * This is an async operation.
		 * @param callback will be called when the screenshot has been taken.
		 * The screenshot is taken exactly after the webviews has rendered.
		 */
		virtual PermissionState TakeScreenshot(TakeScreenshotCallback callback) const = 0;

		/**
		 * This is an async operation.
		 * @param callback will be called when the screenshot has been taken.
		 * The screenshot is taken exactly after GTA:V has rendered it's stuff and before alt:V renders anything custom.
		 */
		virtual PermissionState TakeScreenshotGameOnly(TakeScreenshotCallback callback) const = 0;


		virtual Ref<IWebView> CreateWebView(IResource* res, StringView url, uint32_t drawableHash, StringView targetTexture) = 0;
		virtual Ref<IWebView> CreateWebView(IResource* res, StringView url, Vector2i position, Vector2i size, bool isVisible, bool isOverlay) = 0;
		virtual Ref<IWebSocketClient> CreateWebSocketClient(StringView url, IResource* res) = 0;
		virtual Ref<IHttpClient> CreateHttpClient(IResource* res) = 0;
		virtual Ref<IBlip> CreateBlip(IBlip::BlipType type, Vector3f position) = 0;
		virtual Ref<IBlip> CreateBlip(IBlip::BlipType type, uint32_t entityID) = 0;
		virtual Ref<IBlip> CreateBlip(Vector3f position, float radius) = 0;
		virtual Ref<IBlip> CreateBlip(Vector3f position, float width, float height) = 0;
		virtual Ref<ICheckpoint> CreateCheckpoint(uint8_t type, Vector3f pos, Vector3f next, float radius, float height, alt::RGBA color) = 0;
		virtual Ref<IAudio> CreateAudio(StringView source, float volume, uint32_t category, bool frontend, IResource* res) = 0;
		virtual Ref<IRmlDocument> CreateDocument(const std::string& url, const std::string& currentPath, IResource* res) = 0;

		virtual void SetAngularVelocity(uint32_t entityId, alt::Vector4f velocity) = 0;

		virtual bool IsGameFocused() const = 0;

		virtual void LoadModel(uint32_t hash) = 0;
		virtual void LoadModelAsync(uint32_t hash) = 0;

		virtual bool LoadYtyp(const std::string& path) = 0;
		virtual bool UnloadYtyp(const std::string& path) = 0;

		virtual alt::String HeadshotToBase64(uint8_t id) = 0;

		virtual void SetDlcClothes(int32_t scriptID, uint8_t component, uint16_t drawable, uint8_t texture, uint8_t palette, uint32_t dlc) = 0;
		virtual void SetDlcProps(int32_t scriptID, uint8_t component, uint8_t drawable, uint8_t texture, uint32_t dlc) = 0;
		virtual void ClearProps(int32_t scriptID, uint8_t component) = 0;

		virtual void SetWatermarkPosition(uint8_t pos) = 0;

		virtual uint16_t GetFps() const = 0;
		virtual uint16_t GetPing() const = 0;
		virtual uint64_t GetTotalPacketsSent() const = 0;
		virtual uint32_t GetTotalPacketsLost() const = 0;
		virtual alt::String GetServerIp() const = 0;
		virtual uint16_t GetServerPort() const = 0;
		virtual alt::String GetClientPath() const = 0;

		virtual bool HasLocalMetaData(const std::string& key) const = 0;
		virtual MValue GetLocalMetaData(const std::string& key) const = 0;
		
		virtual PermissionState CopyToClipboard(const std::string& value) = 0;

		virtual void ToggleRmlDebugger(bool state) = 0;
		virtual bool LoadRmlFontFace(IResource* resource, const std::string& path, const std::string& currentPath, const std::string& name, bool italic = false, bool bold = false) const = 0;
		virtual void ToggleRmlControl(bool state) = 0;

		virtual Vector3f WorldToScreen(Vector3f pos) = 0;
		virtual Vector3f ScreenToWorld(Vector2f pos) = 0;
		virtual Vector3f GetCamPos() = 0;
		virtual Vector2i GetScreenResolution() const = 0;

		virtual void SetMinimapComponentPosition(const std::string& name, char alignX, char alignY, Vector2f pos, Vector2f size) = 0;
		virtual void SetMinimapIsRectangle(bool state) = 0;
#endif

#ifdef ALT_SERVER_API // Server methods
		virtual StringView GetRootDirectory() = 0;

		virtual IResource *StartResource(StringView name) = 0;
		virtual void StopResource(StringView name) = 0;
		virtual void RestartResource(StringView name) = 0;

		virtual void TriggerClientEvent(Ref<IPlayer> target, StringView ev, MValueArgs args) = 0;
		virtual void TriggerClientEvent(Array<Ref<IPlayer>> targets, StringView ev, MValueArgs args) = 0;
		virtual void TriggerClientEventForAll(StringView ev, MValueArgs args) = 0;

		virtual void SetSyncedMetaData(const std::string& key, MValue val) = 0;
		virtual void DeleteSyncedMetaData(const std::string& key) = 0;

		virtual Ref<IVehicle> CreateVehicle(uint32_t model, Position pos, Rotation rot) = 0;

		// TODO make enum for types
		virtual Ref<ICheckpoint> CreateCheckpoint(uint8_t type, Position pos, float radius, float height, RGBA color) = 0;

		virtual Ref<IBlip> CreateBlip(Ref<IPlayer> target, IBlip::BlipType type, Position pos) = 0;
		virtual Ref<IBlip> CreateBlip(Ref<IPlayer> target, IBlip::BlipType type, Ref<IEntity> attachTo) = 0;

		virtual Ref<IVoiceChannel> CreateVoiceChannel(bool spatial, float maxDistance) = 0;

		virtual Ref<IColShape> CreateColShapeCylinder(Position pos, float radius, float height) = 0;
		virtual Ref<IColShape> CreateColShapeSphere(Position pos, float radius) = 0;
		virtual Ref<IColShape> CreateColShapeCircle(Position pos, float radius) = 0;
		virtual Ref<IColShape> CreateColShapeCube(Position pos, Position pos2) = 0;
		virtual Ref<IColShape> CreateColShapeRectangle(float x1, float y1, float x2, float y2, float z) = 0;
		virtual Ref<IColShape> CreateColShapePolygon(float minZ, float maxZ, std::vector<Vector2f> points) = 0;

		virtual Array<Ref<IPlayer>> GetPlayersByName(const std::string& name) const = 0;

		virtual uint32_t GetNetTime() const = 0;

		virtual void SetPassword(StringView password) const = 0;
		virtual uint64_t HashServerPassword(StringView password) const = 0;

		virtual void StopServer() = 0;

		virtual const VehicleModelInfo& GetVehicleModelByHash(uint32_t hash) const = 0;

		virtual alt::config::Node GetServerConfig() const = 0;
#endif

		static ICore &Instance()
		{
			return *_instance();
		}
		static void SetInstance(ICore *server) { _instance() = server; }

	protected:
		virtual ~ICore() = default;

	private:
		static ICore *&_instance()
		{
			static ICore *instance = nullptr;
			return instance;
		}
	};
} // namespace alt
