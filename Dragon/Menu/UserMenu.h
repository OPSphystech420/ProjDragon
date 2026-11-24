#pragma once

#include "../MenuLoad/Includes.h"
#include "../Utilities/Singleton.h" 

#include "../Utilities/ConvertUtils.hpp"
#include "../Utilities/magic_enum/magic_enum.hpp"
#include "../Utilities/Format/format.h"
#include "../Utilities/Format/xchar.h"


#include <functional>
#include <algorithm>


#define APP_NAME        "NiggerTool"

enum class RegionType : uint8_t
{
    Region,
    EU,
    NA,
    Asia,
    ANZ
};

enum class DifficultyType : uint8_t
{
    Difficulty,
    Easy,
    Medium,
    Hard,
    Brutal
};

enum class ModeType : uint8_t
{
    Mode,
    PVE,
    PVX,
    PVP
};

struct SessionInfo 
{
    std::string name;
    std::string nameLower;

    uint8_t numPlayers;
    uint8_t maxPlayers;
    
    RegionType region;
    DifficultyType difficulty;
    ModeType mode;

    bool hasPassword;

    std::string ipPort;

    SessionInfo() = default;
    SessionInfo(const SessionInfo& Other) :
        name(Other.name),
        nameLower(Other.nameLower),
        numPlayers(Other.numPlayers),
        maxPlayers(Other.maxPlayers),
        region(Other.region),
        difficulty(Other.difficulty),
        mode(Other.mode),
        hasPassword(Other.hasPassword),
        ipPort(Other.ipPort)
    {}
};

struct PlayerDisplayInfo {
    std::string PlayerName, PlayerNameLower;
    std::string PlayerTribeName;
    uint64_t PlayerId;
    uint64_t TribeId;
};


void GetImTextureViaURL(NSString* const urlString, void*& outTextureID);
void GetImTextureViaData(const unsigned char* bytes, size_t length, void*& outTextureID);

void DrawCrosshair();

std::string ToLower(const std::string& str);

class UserMenu : public Singleton<UserMenu>
{
public:

    void RenderMenu();
    void SaveOnce();

private:
    friend class Singleton<UserMenu>;
    UserMenu();
    ~UserMenu() { };
    
 
/* * * * * * * * * * * * * * * * * * * * * * * * * */
/* * * * * * * * * ~    Init     ~ * * * * * * * * */
    
    ImVec2 SizeWindow; // settings.MenuSize Not used // Does not change in cur impl (bcs we don't resize our windows) <= ImGuiWindowFlags_NoResize
    
    ImGuiIO& io;
    ImGuiStyle& style;

    static constexpr float SideBarWidth = 124;
    
    ImGuiTableFlags tableFlags = ImGuiTableFlags_RowBg |
                            ImGuiTableFlags_Borders |
                            ImGuiTableFlags_Resizable |
                            ImGuiTableFlags_Reorderable |
                            ImGuiTableFlags_ScrollY;
    
    void SetColors();
    void LoadOnce();

/* * * * * * * * * * * * * * * * * * * * * * * * * */
    
/* * * * * * * * * * * * * * * * * * * * * * * * * */
/* * * * * * * * * ~  Rendering  ~ * * * * * * * * */
    
    struct NotchStyle {
        float top_pos;
        float top_span;
        float corner_bevel_px;
        float right_mid;
        float bottom_last_frac;
        
        NotchStyle() :
            top_pos(0.75f),                 // 0..1 along top
            top_span(0.16f),                // fraction of top length
            corner_bevel_px(12.0f),         // 45 connector size
            right_mid(0.50f),               // 0..1 along right (top..diag)
            bottom_last_frac(1.0f/3.0f)     // 2/3 1/3
        {}
    };
    
    float GroupWidth;
    float GroupHeight;
    
    ImDrawList* dl;
    ImDrawList* fg;
    
    ImVec2 pos;
    ImVec2 size;
    
    ImVec2 Snap1px(ImVec2 p) { return ImVec2(IM_TRUNC(p.x + 0.5f), IM_TRUNC(p.y + 0.5f)); }
    ImVec2 SnapFill(ImVec2 p) { return ImVec2(IM_ROUND(p.x), IM_ROUND(p.y)); }
    
    ImVec2 FillConvexPolyVerticalGradient(const ImVec2* pts, int count, ImU32 col_top, ImU32 col_bottom, ImU32 base_col_for_alpha, const float* opt_span_min_y = nullptr, const float* opt_span_max_y = nullptr);
    void DrawGlowGaussian(const ImVec2* pts, int count, ImU32 base_rgb, int passes = 12, float radius_px = 20.0f, float max_alpha = 0.40f);
    void DrawInsetLine_Lean(float sidebar_w, float r, float pad, ImU32 col, float thickness, const NotchStyle& s = {});
    void DrawCompositeWindow(float sidebar_w, float rounding, ImU32 col_sidebar, ImU32 col_main);
/* * * * * * * * * * * * * * * * * * * * * * * * * */
    
    
/* * * * * * * * * * * * * * * * * * * * * * * * * */
/* * * * * * * * * ~   Content   ~ * * * * * * * * */
    void* DragonLogo;
    void* BackgroundTex;
    
/* * * * * * * * * * * * * * * * * * * * * * * * * */
    

    
/*  General  */
    void GeneralHeader();
    
/*  ESP  */
    bool ShouldFilter = false;
    uint16_t currentDinoPage = 0;
    const uint16_t itemsPerPage = 6;
    uint16_t totalDinoFiltered = 0;
    std::string searchDinoBuffer = "";
    std::string searchDinoStrLower = "";

    void ESPHeader();
    void ESPDinos(float totalWidth);
    void ESPOthers(float totalWidth);
    
/*  Misc  */

    std::string unifiedFilter = "";
    
    void MiscHeader();
    
/*  AimBot  */
    void AimBotHeader();
    
/*  Structures  */
    std::string searchBuildBuffer = "";
    
    void BuildHeader();
    
/*  Admin  */
    int selectedItem = 0;
    int DinoValue = 100;
    int ItemValue = 48;
    int StackValue = 6;
    int currentDinoIndex = 0;
    int inputValue = 0;
    
    bool isTamed = true;
    
    int regionIdx = 0;
    
    int AmberValue = 111500;
    int AmberpickupVaule = 100;
    
    int floatIdx = 0;
    
    int posX = 0;
    int posY = 0;
    int posZ = 0;
    
    bool SpawnDung = false;
    bool DestroyDung = false;
    
    std::string searchBufferItem = "";
    std::string searchBufferItemLower = "";
    
    std::string searchBufferDino = "";
    std::string searchBufferDinoLower = "";
    

    void AdminHeader();
    
/*  Settings  */
    bool bColorChanged = false;
    bool bSaveColor = false;
    
    void SettingsHeader();

/* PlayerList */

    uint64_t g_SelectedPlayerID;

    std::string searchPlrBuffer = "";
    std::string searchPlrStrLower = "";

    void PlayerList();
    
/* ServerList */

    SessionInfo* selectedSession = nullptr;

    bool sortByPassword = false;

    bool bIsDispatchActive = false;

    uint16_t currentPage = 0;
    const uint16_t pageSize = 12;
    uint16_t totalFiltered = 0;

    RegionType RegionFilter = RegionType::Region;
    DifficultyType DifficultyFilter = DifficultyType::Difficulty;
    ModeType ModeFilter = ModeType::Mode;

    std::string searchSrvBuffer = "";
    std::string searchSrvStrLower = "";
    // std::wstring serverPassword = L"";

    void ServerList();

    std::string FetchDataFromURL(const std::string& url);

    void ParseJSONData(char* jsonData,
                        std::vector<SessionInfo>& sessions);
    
    
/*   TextInput   */
    bool alertControllerFlag = false;

    template <typename T, typename std::enable_if<std::is_same<T, std::string>::value ||
                                                  std::is_same<T, std::wstring>::value>::type* = nullptr>
    void ShowTextInputAlert(
        NSString* title,
        NSString* message,
        NSString* placeholder,
        NSString* textfield,
        bool includeCancel,
        std::function<void(const T&)> onEnter,
        std::function<void(const T&)> onCancel = nullptr,
        UIKeyboardType Keyboard = UIKeyboardType::UIKeyboardTypeDefault)
    {
        UIAlertController *alertController = [UIAlertController alertControllerWithTitle:title
                                                                                message:message
                                                                        preferredStyle:UIAlertControllerStyleAlert];
        
        [alertController addTextFieldWithConfigurationHandler:^(UITextField * _Nonnull textField) {
            textField.placeholder = placeholder;
            textField.text = textfield;
            textField.keyboardType = Keyboard;
        }];
        
        UIAlertAction *enterAction = [UIAlertAction actionWithTitle:@"Enter"
                                                            style:UIAlertActionStyleDefault
                                                            handler:^(UIAlertAction * _Nonnull action) {
            UITextField *textField = alertController.textFields.firstObject;
            NSString *enteredText = textField.text;
            if (onEnter)
            {
                std::string text([enteredText UTF8String]);

                if constexpr (std::is_same<T, std::string>::value) {
                    onEnter(text);
                } else if constexpr (std::is_same<T, std::wstring>::value) {
                    onEnter(ConvertUtils::convert(enteredText));
                }
            }
        }];
        
        [alertController addAction:enterAction];
        
        if (includeCancel)
        {
            UIAlertAction *cancelAction = [UIAlertAction actionWithTitle:@"Cancel"
                                                                style:UIAlertActionStyleCancel
                                                                handler:^(UIAlertAction * _Nonnull action) {
                if (onCancel) {
                    if constexpr (std::is_same<T, std::string>::value) {
                        onCancel("");
                    } else if constexpr (std::is_same<T, std::wstring>::value) {
                        onCancel(L"");
                    }
                }
            }];
            [alertController addAction:cancelAction];
        }
        
        dispatch_async(dispatch_get_main_queue(), ^{
            UIWindow *window = [UIApplication sharedApplication].windows.firstObject;
            if (window) {
                UIViewController *rootViewController = window.rootViewController;
                if (rootViewController)
                    [rootViewController presentViewController:alertController animated:YES completion:nil];
            }
        });
    }
};

