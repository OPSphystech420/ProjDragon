#include <cstddef>
#include <objc/runtime.h>

#include "../ImGui/DRGui/dr_gui.h"

#include "UserMenu.h"
#include "EnumPage.hpp"
#include "Map.h"
#include "../FrameTaskManager.h"
#include "../Resources/Fonts.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "../Utilities/iOSAlerts.h"

#include "../Utilities/VMTHook.h"
#include "../Utilities/Timer.h"

#define DRAGON_LOGO @""
// TODO: Supply a local logo asset for your own public build.

ImColor red =       ImColor(0.6f, 0.1f, 0.1f);
ImColor green =     ImColor(0.1f, 0.6f, 0.1f);
ImColor blue =      ImColor(0.0f, 0.2f, 0.6f);
ImColor white =     ImColor(1.0f, 1.0f, 1.0f);
ImColor black =     ImColor(0.0f, 0.0f, 0.0f);
ImColor yellow =    ImColor(0.9f, 0.8f, 0.0f);
ImColor orange =    ImColor(0.6f, 0.3f, 0.1f);
ImColor purple =    ImColor(0.4f, 0.1f, 0.5f);
ImColor cyan =      ImColor(0.2f, 0.7f, 0.5f);

ImVec3 lightGreenColor =    ImVec3(0.5f, 1.0f, 0.5f);
ImVec3 redColor =           ImVec3(1.0f, 0.0f, 0.0f);
ImVec3 blueColor =          ImVec3(0.0f, 0.0f, 1.0f);
ImVec3 greenColor =         ImVec3(0.0f, 1.0f, 0.0f);
ImVec3 yellowColor =        ImVec3(1.0f, 1.0f, 0.0f);
ImVec3 cyanColor =          ImVec3(0.0f, 1.0f, 1.0f);
ImVec3 magentaColor =       ImVec3(1.0f, 0.0f, 1.0f);
ImVec3 lightGreyColor =     ImVec3(0.8f, 0.8f, 0.8f);
ImVec3 lightBrownColor =    ImVec3(0.7f, 0.5f, 0.2f);
ImVec3 lightOrangeColor =   ImVec3(1.0f, 0.7f, 0.3f);
ImVec3 lightYellowColor =   ImVec3(1.0f, 1.0f, 0.5f);
ImVec3 lightRedColor =      ImVec3(1.0f, 0.5f, 0.5f);
ImVec3 darkGreyColor =      ImVec3(0.4f, 0.4f, 0.4f);
ImVec3 blackColor =         ImVec3(0.0f, 0.0f, 0.0f);
ImVec3 brownColor =         ImVec3(0.4f, 0.2f, 0.0f);
ImVec3 darkGreenColor =     ImVec3(0.0f, 0.3f, 0.0f);
ImVec3 darkRedColor =       ImVec3(0.5f, 0.0f, 0.0f);
ImVec3 whiteColor =         ImVec3(1.0f, 1.0f, 1.0f);


// -------- // -------- // -------- // -------- // -------- // -------- // -------- // -------- // -------- // -------- //

// ItemType names
static std::vector<const char*> ItemTypeNames = {
    "Misc Consumable",
    "Equipment",
    "Weapon",
    "Ammo",
    "Structure",
    "Resource",
    "Skin",
    "Weapon Attachment",
    "Artifact",
    "None" // instead of MAX
    // ignore EPrimalItemType_MAX
};

// EquipmentType names
static std::vector<const char*> EquipmentTypeNames = {
    "Hat",
    "Shirt",
    "Pants",
    "Boots",
    "Gloves",
    "Dino Saddle",
    "Trophy",
    "Costume",
    "Shield",
    "Collar",
    "None" // instead of MAX
    // ignore EPrimalEquipmentType_MAX
};

// ConsumableType names
static std::vector<const char*> ConsumableTypeNames = {
    "Food",
    "Water",
    "Medicine",
    "Other",
    "None" // instead of MAX
    // ignore EPrimalConsumableType_MAX
};


/* FORCEINLINE bool ImGuiEnumCombo(const char* Label, int& CurrentValue, const std::vector<const char*>& Names)
{
    if (Names.empty())
           return false;

       if (CurrentValue < 0) CurrentValue = 0;
       if (CurrentValue >= (int)Names.size()) CurrentValue = (int)Names.size() - 1;


    const char* CurrentName = Names[CurrentValue];
    if (ImGui::BeginCombo(Label, CurrentName))
    {
        for (int i = 0; i < static_cast<int>(Names.size()); ++i)
        {
            bool IsSelected = (CurrentValue == i);
            if (ImGui::Selectable(Names[i], IsSelected))
            {
                CurrentValue = i;
            }
            if (IsSelected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
        return true;
    }
    return false;
} */


struct ColorEntry {
    ImGuiCol idx;
    ImVec4 color;
    const char* name;
};

const ColorEntry C0L0R[] = { // constexpr
    { ImGuiCol_WindowBg,              DRGui::HexToColorVec4(0x05E8EA, 0.85f), "Side Window" },
    { ImGuiCol_PopupBg,              DRGui::HexToColorVec4(0x091822, 0.85f), "Side Gradient" },
    { ImGuiCol_MenuBarBg,            DRGui::HexToColorVec4(0x011518, 0.80f), "Main Window" },
    { ImGuiCol_ChildBg,              DRGui::HexToColorVec4(0x005566, 0.80f), "Main Gradient" },

    { ImGuiCol_Text,                 DRGui::HexToColorVec4(0xC4E8FA, 1.00f), "Text" },
    { ImGuiCol_TextDisabled,         DRGui::HexToColorVec4(0x82B5BE, 1.00f), "Text Disabled" },

    { ImGuiCol_SliderGrab,           DRGui::HexToColorVec4(0x20DADA, 0.90f), "Widgets" },
    { ImGuiCol_SliderGrabActive,     DRGui::HexToColorVec4(0x20DADA, 1.00f), "Widgets Active" },
    { ImGuiCol_FrameBg,              DRGui::HexToColorVec4(0x000000, 0.25f), "Widgets Hovered" },

    { ImGuiCol_Border,               DRGui::HexToColorVec4(0x05E8EA, 0.35f), "Border" },
};

void UserMenu::SetColors() {
    for (const auto& entry : C0L0R)
        style.Colors[entry.idx] = entry.color;
}

void UserMenu::SaveOnce() {
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];

    for (const auto& entry : C0L0R) {
        ImVec4& color = style.Colors[entry.idx];
        float colorArray[4] = { color.x, color.y, color.z, color.w };

        NSData *colorData = [NSData dataWithBytes:&colorArray length:sizeof(colorArray)];

        NSString *key = [NSString stringWithUTF8String:entry.name];
        [defaults setObject:colorData forKey:key];
    }

    [defaults synchronize];
}

void UserMenu::LoadOnce() {
    ExecutionTimer::Synchronize(201, false);

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    style.WindowRounding    = 10;
    style.ChildRounding     = 0;
    style.FrameRounding     = 0;
    style.PopupRounding     = 0;
    style.ScrollbarRounding = 0;
    style.TabRounding       = 0;

    style.ButtonTextAlign   = { 0.5f, 0.5f };
    style.WindowTitleAlign  = { 0.5f, 0.5f };

    style.FramePadding      = { 6.0f, 6.0f };
    style.WindowPadding     = { 28.0f, 14.0f };
    style.ItemSpacing       = { 14.0f, 6.0f };
    style.ItemInnerSpacing  = { 6.0f, 1.5f };
    style.CellPadding       = { 4.0f, 1.5f };

    style.WindowBorderSize  = 1;
    style.FrameBorderSize   = 1;
    style.PopupBorderSize   = 1;

    style.ScrollbarSize     = 15.0f;
    style.GrabMinSize       = 14.0f;
    style.DisabledAlpha     = 0.5f;

    /* if (settings.MenuSize.x && settings.MenuSize.y) {
       SizeWindow.x = settings.MenuSize.x;
       SizeWindow.y = settings.MenuSize.y;
    } else */ /* if (isIPad)
       SizeWindow = ImVec2(722, 500); // NO IPAD SUPPORT FOR NOW
    else */ SizeWindow = ImVec2(522, 350);

    ImGui::SetNextWindowPos(io.DisplaySize / 2 - SizeWindow / 2); // ImGuiCond_Once
    //  ImGui::SetNextWindowPos(ImVec2(SCREEN_WIDTH / 8, SCREEN_HEIGHT / 12));

    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];

    style.Colors[ImGuiCol_BorderShadow]         = ImVec4(0, 0, 0, 0);
    style.Colors[ImGuiCol_ResizeGrip]           = ImVec4(0, 0, 0, 0);
    style.Colors[ImGuiCol_ResizeGripHovered]    = ImVec4(0, 0, 0, 0);
    style.Colors[ImGuiCol_ResizeGripActive]     = ImVec4(0, 0, 0, 0);
    style.Colors[ImGuiCol_ScrollbarBg]          = ImVec4(0, 0, 0, 0);

    style.Colors[ImGuiCol_TableRowBgAlt]          = ImVec4(0, 0, 0, 0);
    style.Colors[ImGuiCol_TableRowBg]          = ImVec4(0, 0, 0, 0);
    style.Colors[ImGuiCol_TableHeaderBg]          = ImVec4(0, 0, 0, 0);
    style.Colors[ImGuiCol_TableBorderStrong]          = ImVec4(0, 0, 0, 0);
    style.Colors[ImGuiCol_TableBorderLight]          = ImVec4(0, 0, 0, 0);
    style.Colors[ImGuiCol_TableRowBg]          = ImVec4(0, 0, 0, 0);
    style.Colors[ImGuiCol_TableRowBgAlt]          = ImVec4(0, 0, 0, 0);

    for (const auto& entry : C0L0R) {
        NSString *key = [NSString stringWithUTF8String:entry.name];
        NSData *colorData = [defaults objectForKey:key];

        if (colorData) {
            float colorArray[4];
            [colorData getBytes:&colorArray length:sizeof(colorArray)];

            ImVec4& color = style.Colors[entry.idx];
            color.x = colorArray[0];
            color.y = colorArray[1];
            color.z = colorArray[2];
            color.w = colorArray[3];
        } else {
            SetColors();
            break;
        }
    }

    style.Colors[ImGuiCol_Separator]            = style.Colors[ImGuiCol_Border];
    style.Colors[ImGuiCol_SeparatorHovered]     = style.Colors[ImGuiCol_Border];
    style.Colors[ImGuiCol_SeparatorActive]      = style.Colors[ImGuiCol_Border];

    style.Colors[ImGuiCol_Button]               = style.Colors[ImGuiCol_FrameBg];
    style.Colors[ImGuiCol_ButtonHovered]        = style.Colors[ImGuiCol_FrameBgHovered];
    style.Colors[ImGuiCol_ButtonActive]         = style.Colors[ImGuiCol_FrameBgActive];

    style.Colors[ImGuiCol_FrameBgHovered]       = style.Colors[ImGuiCol_FrameBg];
    style.Colors[ImGuiCol_FrameBgActive]        = style.Colors[ImGuiCol_FrameBg];

    style.Colors[ImGuiCol_Header]               = style.Colors[ImGuiCol_FrameBg];
    style.Colors[ImGuiCol_HeaderHovered]        = style.Colors[ImGuiCol_FrameBgHovered];
    style.Colors[ImGuiCol_HeaderActive]         = style.Colors[ImGuiCol_FrameBgActive];

    style.Colors[ImGuiCol_ScrollbarGrab]        = style.Colors[ImGuiCol_SliderGrab];
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = style.Colors[ImGuiCol_SliderGrab];
    style.Colors[ImGuiCol_ScrollbarGrabActive]  = style.Colors[ImGuiCol_SliderGrab];

    style.Colors[ImGuiCol_CheckMark]            = style.Colors[ImGuiCol_SliderGrabActive];
}

UserMenu::UserMenu() : io(ImGui::GetIO()), style(ImGui::GetStyle()), DragonLogo(nullptr)
{
    LoadOnce();

    GetImTextureViaURL(
       DRAGON_LOGO,
       DragonLogo
    );
}

// -------- // -------- // -------- // -------- // -------- // -------- // -------- // -------- // -------- // -------- //

// NOTE: ImTextureID typedef patched from (void*) to (ImU64)

void GetImTextureViaURL(NSString* const urlString, void*& outTextureID)
{ /* (EXTRA: Texture class - clean + store)*/
    outTextureID = nullptr;

    NSURL* const url = [NSURL URLWithString:urlString];
    if (!url)
        return;

    __block void** const blockTextureID = &outTextureID;

    NSURLSessionDataTask *downloadTask = [[NSURLSession sharedSession] dataTaskWithURL:url
                                                                     completionHandler:^(NSData * _Nullable data, NSURLResponse * _Nullable response, NSError * _Nullable error) {
        if (error || !data)
            return;

        UIImage* const image = [UIImage imageWithData:data];
        id<MTLDevice> const device = MTLCreateSystemDefaultDevice();
        if (!image || !device)
            return;

        MTKTextureLoader * const textureLoader = [[MTKTextureLoader alloc] initWithDevice:device];
        if (!textureLoader)
            return;

        NSDictionary * const textureLoaderOptions = @{
            MTKTextureLoaderOptionSRGB : @NO,
            MTKTextureLoaderOptionTextureUsage : @(MTLTextureUsageShaderRead | MTLTextureUsageRenderTarget),
            MTKTextureLoaderOptionTextureStorageMode : @(MTLStorageModePrivate)
        };

        NSError *textureError = nil;

        id<MTLTexture> const metalTexture = [textureLoader newTextureWithCGImage:image.CGImage
                                                                          options:textureLoaderOptions
                                                                            error:&textureError];
        if (!metalTexture || textureError)
            return;

        void* const imguiTextureID_ptr = (__bridge_retained void *)(metalTexture);

        dispatch_async(dispatch_get_main_queue(), ^{
            *blockTextureID = imguiTextureID_ptr;
        });
    }];

    [downloadTask resume];
}

// -------- // -------- // -------- // -------- // -------- // -------- // -------- // -------- // -------- // -------- //
// -------- // -------- // -------- // -------- // -------- // -------- // -------- // -------- // -------- // -------- //
// -------- // -------- // -------- // -------- // -------- // -------- // -------- // -------- // -------- // -------- //
// -------- // -------- // -------- // -------- // -------- // -------- // -------- // -------- // -------- // -------- //
// -------- // -------- // -------- // -------- // -------- // -------- // -------- // -------- // -------- // -------- //

#include "../Utilities/Core.h"


auto add_on  = ImGui_ImplMetal_AdditiveOnCallback();
auto add_off = ImGui_ImplMetal_AdditiveOffCallback();

FORCEINLINE ImVec2 UserMenu::FillConvexPolyVerticalGradient(
    const ImVec2* pts, int count,
    ImU32 col_top, ImU32 col_bottom,
    ImU32 base_col_for_alpha,
    const float* opt_span_min_y /*= nullptr*/,
    const float* opt_span_max_y /*= nullptr*/)
{
    IM_ASSERT(count >= 3);
    const int vtx_start = dl->VtxBuffer.Size;

    dl->AddConvexPolyFilled(pts, count, base_col_for_alpha);

    const int vtx_end = dl->VtxBuffer.Size;

    float local_min_y = pts[0].y, local_max_y = pts[0].y;
    for (int i = 1; i < count; ++i) {
        const float y = pts[i].y;
        local_min_y = (y < local_min_y) ? y : local_min_y;
        local_max_y = (y > local_max_y) ? y : local_max_y;
    }

    const float span_min_y = opt_span_min_y ? *opt_span_min_y : local_min_y;
    const float span_max_y = opt_span_max_y ? *opt_span_max_y : local_max_y;

    const bool degenerate = fabsf(span_max_y - span_min_y) < 1e-6f;
    ImGui::ShadeVertsLinearColorGradientKeepAlpha(
        dl, vtx_start, vtx_end,
        ImVec2(0.0f, span_min_y),
        ImVec2(0.0f, degenerate ? span_min_y : span_max_y),
        degenerate ? col_top : col_top,
        degenerate ? col_top : col_bottom
    );

    return ImVec2(local_min_y, local_max_y);
}


FORCEINLINE void UserMenu::DrawGlowGaussian(
    const ImVec2* pts, int count,
    ImU32 base_rgb,
    int passes,
    float radius_px,
    float max_alpha)
{
    if (count <= 1 || passes <= 0 || radius_px <= 0.0f || max_alpha <= 0.0f)
        return;

    const int P = ImClamp(passes, 1, 64);
    float weights[64];

    const float sigma = radius_px * 0.5f;
    const float step  = radius_px / (float)P;

    float sum = 0.0f;
    for (int i = 0; i < P; ++i) {
        const float t = (i + 1) * step;
        const float x = t / sigma;
        const float w = expf(-0.5f * x * x);
        weights[i] = w;
        sum += w;
    }
    if (sum <= 0.0f) return;
    const float alpha_scale = max_alpha / sum;

    //dl->PushClipRectFullScreen();
    const ImGuiViewport* vp = ImGui::GetMainViewport();
    dl->PushClipRect(vp->Pos, vp->Pos + vp->Size, false);
    dl->AddCallback(add_on,  nullptr);
    for (int i = P - 1; i >= 0; --i) {
        const float a = alpha_scale * weights[i];
        const ImU32 col = (base_rgb & 0x00FFFFFF) | ((ImU32)(ImClamp(a, 0.0f, 1.0f) * 255.0f) << IM_COL32_A_SHIFT);
        const float thickness = (i + 1) * step * 2.0f;   // symmetric outward growth
        dl->AddPolyline(pts, count, col, ImDrawFlags_Closed, thickness);
    }
    dl->AddCallback(add_off, nullptr);
    dl->AddCallback(ImDrawCallback_ResetRenderState, nullptr);
    dl->PopClipRect();
}

FORCEINLINE void UserMenu::DrawInsetLine_Lean(
    float sidebar_w, float r, float pad,
    ImU32 col, float thickness,
    const NotchStyle& s)
{
    pad = ImClamp(pad, 0.0f, ImMax(0.0f, r - 0.5f));

    const float Lx = pos.x + sidebar_w;
    const float Rx = pos.x + size.x;
    const float Ty = pos.y + r;
    const float By = pos.y + size.y - r;

    const float ixL = Lx + pad;
    const float ixR = Rx - pad;
    const float iyT = Ty + pad;
    const float iyB = By - pad;

    const float C_edge = Rx + (pos.y + size.y) - 2.0f * r - pad * 1.41421356f;
    const float d = ImClamp(pad - 4.0f, 1.0f, pad);
    const float rightDepth = d * 0.9f;

    const float lenTop   = ixR - ixL;
    const float yR1_edge = C_edge - ixR;
    const float lenRight = yR1_edge - iyT;

    const float topStart = ixL + lenTop * ImClamp(s.top_pos, 0.05f, 0.90f);
    const float topEnd   = ImMin(ixR - 2.0f,
                                 topStart + ImClamp(lenTop * ImClamp(s.top_span, 0.08f, 0.40f), 8.0f, lenTop - 8.0f));

    const float bevel = ImClamp(s.corner_bevel_px, 2.0f, 0.5f * ImMin(lenTop, lenRight));

    const float yRightMid = iyT + lenRight * ImClamp(s.right_mid, 0.2f, 0.8f);
    const float halfSpan  = ImClamp(0.5f * lenRight - 4.0f, 8.0f, 0.5f * lenRight - 2.0f);
    const float yR0       = ImMax(iyT + 2.0f, yRightMid - halfSpan * 0.5f);
    const float yR1_inner = (C_edge - ixR) - rightDepth;

    const float C_diag = C_edge - 2.0f * rightDepth;
    const ImVec2 i2    = Snap1px(ImVec2(ixR - rightDepth, C_diag - (ixR - rightDepth)));
    const ImVec2 i3    = Snap1px(ImVec2(C_diag - iyB,     iyB));

    const float bottomDiagXEdge = C_edge - iyB;
    const float lenBottom       = bottomDiagXEdge - ixL;
    const float bxStart         = bottomDiagXEdge - lenBottom * ImClamp(s.bottom_last_frac, 0.15f, 0.80f);

    ImVec2 pts[16];
    int n = 0;
    pts[n++] = Snap1px(ImVec2(ixL,                 iyT));
    pts[n++] = Snap1px(ImVec2(topStart,            iyT));
    pts[n++] = Snap1px(ImVec2(topStart + d,        iyT - d));
    pts[n++] = Snap1px(ImVec2(topEnd   - d,        iyT - d));
    pts[n++] = Snap1px(ImVec2(topEnd,              iyT));
    pts[n++] = Snap1px(ImVec2(ixR - bevel,         iyT));
    pts[n++] = Snap1px(ImVec2(ixR,                 iyT + bevel));
    pts[n++] = Snap1px(ImVec2(ixR,                 yR0));
    pts[n++] = Snap1px(ImVec2(ixR - rightDepth,    yR0 + rightDepth));
    pts[n++] = Snap1px(ImVec2(ixR - rightDepth,    yR1_inner));
    pts[n++] = i2;
    pts[n++] = i3;
    pts[n++] = Snap1px(ImVec2(bxStart,             iyB));
    pts[n++] = Snap1px(ImVec2(bxStart - rightDepth,iyB - rightDepth));
    pts[n++] = Snap1px(ImVec2(ixL,                 iyB - rightDepth));

    const ImDrawListFlags saved = dl->Flags;
    dl->Flags &= ~ImDrawListFlags_AntiAliasedLines;
    dl->AddPolyline(pts, n, col, ImDrawFlags_None, ImClamp(thickness, 0.5f, 2.0f));
    dl->Flags = saved;
}

FORCEINLINE void UserMenu::DrawCompositeWindow(
    float sidebar_w, float rounding,
    ImU32 col_sidebar, ImU32 col_main)
{
    IM_ASSERT(dl != nullptr);
    const float r = ImClamp(rounding, 0.0f, ImMin(ImMin(size.x, size.y) * 0.5f, sidebar_w));

    ImVec2 a[6] = {
        Snap1px(pos + ImVec2(r,             0)),
        Snap1px(pos + ImVec2(sidebar_w,     0)),
        Snap1px(pos + ImVec2(sidebar_w,     size.y - r)),
        Snap1px(pos + ImVec2(sidebar_w - r, size.y)),
        Snap1px(pos + ImVec2(0,             size.y)),
        Snap1px(pos + ImVec2(0,             r)),
    };

    const ImU32 sb_top    = ImGui::GetColorU32(ImGuiCol_PopupBg);
    const ImU32 sb_bottom = col_sidebar;
    FillConvexPolyVerticalGradient(a, IM_ARRAYSIZE(a), sb_top, sb_bottom, col_sidebar);

    ImVec2 b[5] = {
        SnapFill(pos + ImVec2(sidebar_w,  r)),
        SnapFill(pos + ImVec2(size.x,     r)),
        SnapFill(pos + ImVec2(size.x,     size.y - 2.0f*r)),
        SnapFill(pos + ImVec2(size.x - r, size.y - r)),
        SnapFill(pos + ImVec2(sidebar_w,  size.y - r)),
    };


    const ImU32 mn_top    = ImGui::GetColorU32(ImGuiCol_ChildBg);
    const ImU32 mn_bottom = col_main;

    float spanMin = pos.y + 0.0f;
    float spanMax = pos.y + ImMax(0.0f, size.y - 2.0f * r);

    bool show_banner = false;
    float w_mid_m = 0.48f;

    NotchStyle sty;
    switch (menuState.mainPage) {
        case MenuPage::General:
            sty.top_pos          = 0.15f;
            sty.top_span         = 0.23f;
            sty.corner_bevel_px  = 12.0f;
            sty.right_mid        = 0.75f;
            sty.bottom_last_frac = 2.0f/3.0f;
            show_banner = (r > 0.0f);
            w_mid_m = 0.46f;
            break;
        case MenuPage::ESP:
            sty.top_pos          = 0.07f;
            sty.top_span         = 0.18f;
            sty.corner_bevel_px  = 12.0f;
            sty.right_mid        = 0.95f;
            sty.bottom_last_frac = 1.0f/3.0f;
            show_banner = (r > 0.0f);
            w_mid_m = 0.41f;
            break;
        case MenuPage::Misc:
            sty.top_pos          = 0.00f;
            sty.top_span         = 0.23f;
            sty.corner_bevel_px  = 14.0f;
            sty.right_mid        = 0.55f;
            sty.bottom_last_frac = 1.0f/6.0f;
            show_banner = (r > 0.0f);
            w_mid_m = 0.37f;
            break;
        case MenuPage::AimBot:
            sty.top_pos          = 0.60f;
            sty.top_span         = 0.33f;
            sty.corner_bevel_px  = 10.0f;
            sty.right_mid        = 0.85f;
            sty.bottom_last_frac = 4.0f/5.0f;
            break;
        case MenuPage::Structures:
            sty.top_pos          = 0.19f; // 0.35f;
            sty.top_span         = 0.25f; // 0.42f
            sty.corner_bevel_px  = 10.0f;
            sty.right_mid        = 0.65f;
            sty.bottom_last_frac = 1.0f/4.0f;
            show_banner = (r > 0.0f);
            w_mid_m = 0.47f;
            break;
        case MenuPage::Admin:
            sty.top_pos          = 0.03f;
            sty.top_span         = 0.19f;
            sty.corner_bevel_px  = 12.0f;
            sty.right_mid        = 1.0f;
            sty.bottom_last_frac = 0.90f;
            show_banner = (r > 0.0f);
            w_mid_m = 0.34f;
            break;
        case MenuPage::Settings:
            sty.top_pos          = 0.45f;
            sty.top_span         = 0.42f; // 0.24f
            sty.corner_bevel_px  = 17.0f;
            sty.right_mid        = 0.45f;
            sty.bottom_last_frac = 0.50f;
            break;
        default:
            break;
    }

    const ImDrawListFlags saved = dl->Flags;

    if (show_banner)
        dl->Flags &= ~ImDrawListFlags_AntiAliasedFill;

    FillConvexPolyVerticalGradient(b, IM_ARRAYSIZE(b),
                                   mn_top, mn_bottom, col_main,
                                   &spanMin, &spanMax);

    if (show_banner)
    {
        const float x_mid_local = w_mid_m * (sidebar_w + size.x);

        ImVec2 trap[4] = {
            SnapFill(pos + ImVec2(x_mid_local - r, r)),
            SnapFill(pos + ImVec2(size.x,          r)),
            SnapFill(pos + ImVec2(size.x,          0)),
            SnapFill(pos + ImVec2(x_mid_local,     0)),
        };

        FillConvexPolyVerticalGradient(trap, IM_ARRAYSIZE(trap),
                                       mn_top, mn_bottom, col_main,
                                       &spanMin, &spanMax);

        if (menuState.mainPage == MenuPage::Structures) {
            ImVec2 trap_tur[4] = {
                SnapFill(pos + ImVec2(sidebar_w, r)),
                SnapFill(pos + ImVec2(size.x / 2 - r * 5,          r)),
                SnapFill(pos + ImVec2(size.x / 2 - r * 6,          0)),
                SnapFill(pos + ImVec2(sidebar_w,     0)),
            };

            FillConvexPolyVerticalGradient(trap_tur, IM_ARRAYSIZE(trap_tur),
                                           mn_top, mn_bottom, col_main,
                                           &spanMin, &spanMax);
        }

        dl->Flags = saved;

    }

    const float pad      = 16.0f;
    const ImU32  lineCol = ImGui::GetColorU32(ImGuiCol_Border);

    DrawInsetLine_Lean(sidebar_w, r, pad, lineCol, /*thickness=*/1.0f, sty);

    const ImU32 glowRGB = ImGui::GetColorU32(ImGuiCol_Border);
    DrawGlowGaussian(a, IM_ARRAYSIZE(a), glowRGB, /*passes=*/24, /*radius_px=*/15.5f, /*max_alpha=*/0.42f);
}

// -------- // -------- // -------- // -------- // -------- // -------- // -------- // -------- // -------- // -------- //
// -------- // -------- // -------- // -------- // -------- // -------- // -------- // -------- // -------- // -------- //
// -------- // -------- // -------- // -------- // -------- // -------- // -------- // -------- // -------- // -------- //
// -------- // -------- // -------- // -------- // -------- // -------- // -------- // -------- // -------- // -------- //
// -------- // -------- // -------- // -------- // -------- // -------- // -------- // -------- // -------- // -------- //


void UserMenu::RenderMenu()
{
    ExecutionTimer::Synchronize(202, true);

    if (bSaveColor && menuState.mainPage != MenuPage::Settings)
    {
        SaveOnce(); bSaveColor = false;
    }


    ImFont* font = ImGui::GetFont();
    // font->Scale = 12.f / font->LegacySize;

    // float TabRadioWidth = IconFont->FontSize * 3.0f; // ~60.f
    // float SideBarWidth = style.WindowPadding.x * 2.0f + TabRadioWidth;
    // float SubTabHeight = ImGui::GetFontSize() * 2 + style.WindowPadding.y * 2;

    /* if (isIPad) { // NO IPAD SUPPORT FOR NOW
        SideBarWidth += style.WindowPadding.x * 2.0f;
        // TabRadioWidth += style.WindowPadding.x * 2.0f;
    } */

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize;
    if (!settings.AllowWindowMove) window_flags |= ImGuiWindowFlags_NoMove;

    ImGui::SetNextWindowSize(SizeWindow, ImGuiCond_Once);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2());
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
    ImGui::Begin(APP_NAME, nullptr, window_flags);
    ImGui::PopStyleVar(2);
    // Rendering
    {
        pos = ImGui::GetWindowPos();
        size = ImGui::GetWindowSize();
        // settings.MenuSize = size;

        const ImU32 colSidebar = ImGui::GetColorU32(ImGuiCol_WindowBg);
        const ImU32 colMain    = ImGui::GetColorU32(ImGuiCol_MenuBarBg);

        dl = ImGui::GetWindowDrawList();
        fg = ImGui::GetForegroundDrawList();

        DrawCompositeWindow(
            SideBarWidth,
            style.WindowRounding,
            colSidebar, colMain
        );

    }
    // Content
    {
        // subtabs
        {
            auto [startSubPage, endSubPage] = GetSubRange(menuState.mainPage);
            if (startSubPage != SubPage::NONE) {
                int start = static_cast<int>(startSubPage);
                int end = static_cast<int>(endSubPage);

                float total = style.ItemSpacing.x;

                const auto& SubPageNames = EnumNameCache::GetInstance().GetSubPageNames();

                for (int i = start; i <= end; ++i)
                {
                    auto it = SubPageNames.find(static_cast<SubPage>(i));
                    const char* label = (it != SubPageNames.end()) ? it->second : "???";

                    total += ImGui::CalcTextSize(label).x + style.FramePadding.x * 2;
                }

                if (menuState.mainPage == MenuPage::Structures) {
                    ImGui::SetCursorPosX(25 + SideBarWidth);

                    DRGui::RadioFrameText(SubPageNames.at(SubPage::Turrets), reinterpret_cast<int*>(&menuState.subPages[MenuPage::Structures]), static_cast<int>(SubPage::Turrets));


                    ImGui::SameLine();
                }

                ImGui::SetCursorPosX(size.x - total);

                ImGui::BeginGroup();
                {

                    for (int i = start; i <= end; ++i)
                    {
                        SubPage subPage = static_cast<SubPage>(i);
                        if (subPage == SubPage::Turrets)
                            continue;
                        auto it = SubPageNames.find(subPage);
                        const char* label = (it != SubPageNames.end()) ? it->second : "???";

                        int& currentSubPage = reinterpret_cast<int&>(menuState.subPages[menuState.mainPage]);

                        if (DRGui::RadioFrameText(label, &currentSubPage, static_cast<int>(subPage)))
                        {
                            // Notify, if needed
                        }

                        if (i < end)
                            ImGui::SameLine();
                    }
                }
                ImGui::EndGroup();
            }
        }

        ImGui::SetCursorScreenPos(ImGui::GetWindowPos());
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10, 10));
        // SideBar
        {
            ImGui::BeginChild("SideBar", ImVec2(SideBarWidth, size.y), ImGuiChildFlags_AlwaysUseWindowPadding, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration);
            {

                float fUsableWidth = ImTrunc(ImGui::CalcItemSize(ImVec2(-0.1f, 0), 0, 0).x);
                ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, style.WindowPadding.y)); {

                    const auto& MenuPageNames = EnumNameCache::GetInstance().GetMenuPageNames();

                    DRGui::RadioFrame( // General
                                      MenuPageNames.at(MenuPage::General),
                                      reinterpret_cast<int*>(&menuState.mainPage),
                                      static_cast<int>(MenuPage::General),
                                      ImVec2(fUsableWidth, ImGui::GetFrameHeight())
                                      );

                    DRGui::RadioFrame( // ESP
                                      MenuPageNames.at(MenuPage::ESP),
                                      reinterpret_cast<int*>(&menuState.mainPage),
                                      static_cast<int>(MenuPage::ESP),
                                      ImVec2(fUsableWidth, ImGui::GetFrameHeight())
                                      );

                    DRGui::RadioFrame( // Misc
                                      MenuPageNames.at(MenuPage::Misc),
                                      reinterpret_cast<int*>(&menuState.mainPage),
                                      static_cast<int>(MenuPage::Misc),
                                      ImVec2(fUsableWidth, ImGui::GetFrameHeight())
                                      );

                    DRGui::RadioFrame( // AimBot
                                      MenuPageNames.at(MenuPage::AimBot),
                                      reinterpret_cast<int*>(&menuState.mainPage),
                                      static_cast<int>(MenuPage::AimBot),
                                      ImVec2(fUsableWidth, ImGui::GetFrameHeight())
                                      );

                    DRGui::RadioFrame( // Structures
                                      MenuPageNames.at(MenuPage::Structures),
                                      reinterpret_cast<int*>(&menuState.mainPage),
                                      static_cast<int>(MenuPage::Structures),
                                      ImVec2(fUsableWidth, ImGui::GetFrameHeight())
                                      );

                    DRGui::RadioFrame( // Admin
                                      MenuPageNames.at(MenuPage::Admin),
                                      reinterpret_cast<int*>(&menuState.mainPage),
                                      static_cast<int>(MenuPage::Admin),
                                      ImVec2(fUsableWidth, ImGui::GetFrameHeight())
                                      );

                    DRGui::RadioFrame( // Settings
                                      MenuPageNames.at(MenuPage::Settings),
                                      reinterpret_cast<int*>(&menuState.mainPage),
                                      static_cast<int>(MenuPage::Settings),
                                      ImVec2(fUsableWidth, ImGui::GetFrameHeight())
                                      );

                } ImGui::PopStyleVar();

                ImVec2 logo_size(74, 74);
                if (DragonLogo) {
                    float x = (SideBarWidth - logo_size.x) * 0.5f;
                    float y = size.y - logo_size.y - style.WindowPadding.y;

                    ImGui::SetCursorPos(ImVec2(x, y));
                    ImGui::ImageWithBg((intptr_t)DragonLogo, logo_size, ImVec2(0, 0), ImVec2(1, 1), ImVec4(), ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
                    ImGui::Dummy(logo_size);
                } else {
                    ImGui::Dummy(logo_size);
                }
            }
            ImGui::EndChild();
        }
        ImGui::PopStyleVar();//  ?  ImGui::PopStyleVar(2); <--

        ImGui::SetCursorScreenPos(pos + ImVec2(SideBarWidth, font->LegacySize + style.CellPadding.y * 3));
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(20, 14));
        ImGui::BeginChild("Main", ImVec2(size.x - SideBarWidth, size.y - (font->LegacySize + style.CellPadding.y * 3)), ImGuiChildFlags_AlwaysUseWindowPadding, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration);
        ImGui::PopStyleVar();
        {
            GroupWidth = size.x - SideBarWidth - style.WindowPadding.x * 2;
            GroupHeight = size.y - style.WindowRounding * 6 + 4.0f - style.ItemSpacing.y * 4;

            if (menuState.mainPage == MenuPage::ESP && menuState.subPages[MenuPage::ESP] == SubPage::Other)
            {
                ImGui::BeginChild("SubSubTab", ImVec2(GroupWidth, 2 * GroupHeight / 5), ImGuiChildFlags_Borders, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration); {
                    auto [startSubEsp, endSubEsp] = GetSubSubRange(SubPage::Other);

                    int startEsp = static_cast<int>(startSubEsp);
                    int endEsp = static_cast<int>(endSubEsp);

                    const auto& SubEspPageNames = EnumNameCache::GetInstance().GetSubSubPageNames();

                    ImGui::PushFont(NULL, style.FontSizeBase * 1.5f);
                    for (int i = startEsp; i <= endEsp; ++i)
                    {
                        SubSubPage subEspPage = static_cast<SubSubPage>(i);
                        auto it = SubEspPageNames.find(subEspPage);
                        const char* label = (it != SubEspPageNames.end()) ? it->second : "???";

                        int& currentSubEspPage = reinterpret_cast<int&>(menuState.subSubPages[SubPage::Other]);

                        if (DRGui::RadioFrameText(label, &currentSubEspPage, static_cast<int>(subEspPage)))
                        {
                            // Notify, if needed
                        }ImGui::Spacing();
                    }
                    ImGui::PopFont();
                } ImGui::EndChild();
                // ImGui::SameLine();
                ImGui::Separator();
            }

            ImGui::Spacing();
            // ImGui::Dummy(ImVec2(style.ItemSpacing.x, style.ItemSpacing.y * 3));

            switch (menuState.mainPage) {
                case MenuPage::General:
                    GeneralHeader();
                    break;
                case MenuPage::ESP:
                    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(20, 14));
                    ESPHeader();
                    ImGui::PopStyleVar();
                    break;

                case MenuPage::Misc:
                    MiscHeader();
                    break;

                case MenuPage::AimBot:
                    AimBotHeader();
                    break;

                case MenuPage::Structures:
                    BuildHeader();
                    break;

                case MenuPage::Admin:
                    AdminHeader();
                    break;

                case MenuPage::Settings:
                    SettingsHeader();
                    break;
                default:
                    break;
            }
        }
        ImGui::EndChild();
    }
    ImGui::End();
}


#pragma mark - Genral Header -

/* * * * * * * * * * * * * * * * * * * * * * */
/* * * * * *  Genral Header Begin  * * * * * */
/* * * * * * * * * * * * * * * * * * * * * * */

void UserMenu::GeneralHeader() {
    ExecutionTimer::Synchronize(203, false);

    switch (menuState.subPages[MenuPage::General])
    {
        case SubPage::General:
        {
            ImGui::Spacing();
            SubSubPage curSub = menuState.subSubPages[SubPage::General];
            if (curSub == SubSubPage::Player) {
                ImGui::PushItemWidth((size.x - SideBarWidth - 50));
                DRGui::SliderFloat("Player Speed", &settings.PlayerSpeed, 1.0f, 12.0f);
                DRGui::SliderFloat("Dino Speed", &settings.DinoSpeed, 1.0f, 12.0f);
                DRGui::SliderFloat("Field Of View", &settings.FOV, 1.0f, 1.75f);
                DRGui::SliderFloat("Free Cam Distance", &settings.FreeCamDistance, 1.0f, 75.f);
                DRGui::SliderFloat("TPV Offset X", &settings.TPVCameraOffsetX, -150.0f, 150.0f);
                DRGui::SliderFloat("TPV Offset Y", &settings.TPVCameraOffsetY, -200.0f, 200.0f);
                DRGui::SliderFloat("Framerate Limit", &settings.FPS, 1.0f, 120.f);
                ImGui::PopItemWidth();
            } else if (curSub == SubSubPage::World) {
                DRGui::CheckBox("World Settings", &settings.EnableTime);
                ImGui::PushItemWidth((size.x - SideBarWidth - 50));
                DRGui::SliderFloat("Sky Cycle", &settings.DayCycleSky, 1, 10);
                DRGui::SliderFloat("Day Cycle", &settings.DayCycle, 30, 120);
                DRGui::SliderFloat("Shadows", &settings.DirLight, 1, 100);
                DRGui::SliderFloat("Reflection", &settings.ReflectionMult, 10, 120);
                ImGui::PopItemWidth();
            } else if (curSub == SubSubPage::Color) {
                ImGui::PushFont(NULL, style.FontSizeBase * 1.5f);
                ImGui::Text("Player Colors");
                ImGui::PopFont();
                ImGui::Spacing();
                ImGui::Columns(2, nullptr, false);

                DRGui::CheckBox("Permenant", &settings.UsePermenantColors);
                DRGui::ColorEdit3("Body##1", settings.PermBodyColor);
                DRGui::ColorEdit3("Hair##1", settings.PermHairColor);
                ImGui::NextColumn();
                DRGui::CheckBox("Dynamic", &settings.UseDynamicColors);
                DRGui::ColorEdit3("Body##2", settings.DynamicBodyColor);
                DRGui::ColorEdit3("Hair##2", settings.DynamicHairColor);
                ImGui::EndColumns();
            } else if (curSub == SubSubPage::Materials) {


                static std::array<const char*, 25> GiveItemNames =
                {
                    "Silica Pearls",
                    "Thatch",
                    "Fiber",
                    "Leech Blood",
                    "Sap",
                    "Metal",
                    "Charcoal",
                    "Angler Gel",
                    "Sparkpowder",
                    "Oil",
                    "Obsidian",
                    "Pelt",
                    "Metal Ingot",
                    "Stone",
                    "Wood",
                    "Hide",
                    "Crystal",
                    "Gasoline",
                    "Cementing Paste",
                    "Chitin",
                    "Electronics",
                    "Flint",
                    "Polymer",
                    "Biotoxin",
                    "Black Pearl"
                };


                if (DRGui::Button("Spawn Material", ImVec2((size.x - SideBarWidth) - 50,0)))
                {
                    ShooterPlayerControllerQueue.Add(SpawnMaterials);
                }

                ImGui::PushItemWidth((size.x - SideBarWidth) - 50);

                DRGui::SliderInt("Material Amount", &settings.MaterialAmount, 1, 5000);


                ImGui::ListBox("##MaterisSpawn", &settings.MaterialIndex, GiveItemNames.data(),
                                   static_cast<int>(GiveItemNames.size()), 7);

                ImGui::PopItemWidth();
            }
            ImGui::SetCursorPos(ImVec2(style.WindowPadding.x, size.y * 0.78f));
            ImGui::PushFont(NULL, style.FontSizeBase * 1.5f);
            const auto& SubSubPageNames = EnumNameCache::GetInstance().GetSubSubPageNames();
            DRGui::RadioFrameText(SubSubPageNames.at(SubSubPage::Player), reinterpret_cast<int*>(&menuState.subSubPages[SubPage::General]), static_cast<int>(SubSubPage::Player));
            ImGui::SameLine();
            DRGui::RadioFrameText(SubSubPageNames.at(SubSubPage::World), reinterpret_cast<int*>(&menuState.subSubPages[SubPage::General]), static_cast<int>(SubSubPage::World));
            ImGui::SameLine();
            DRGui::RadioFrameText(SubSubPageNames.at(SubSubPage::Color), reinterpret_cast<int*>(&menuState.subSubPages[SubPage::General]), static_cast<int>(SubSubPage::Color));
            ImGui::SameLine();
            DRGui::RadioFrameText(SubSubPageNames.at(SubSubPage::Materials), reinterpret_cast<int*>(&menuState.subSubPages[SubPage::General]), static_cast<int>(SubSubPage::Materials));
            ImGui::PopFont();
        }
            break;
        case SubPage::Server_List:
            ServerList();
            break;
        case SubPage::Players_List:
            PlayerList();
            break;
        default:
            break;
    }
}

/* * * * * *  Genral Header End   * * * * * */



#pragma mark - ESP Header -

/* * * * * * * * * *  * * * * * * * * * */
/* * * * * * ESP Header Begin * * * * * */
/* * * * * * * * * *  * * * * * * * * * */
void UserMenu::ESPHeader() {
    float totalWidth = size.x - SideBarWidth;
    switch (menuState.subPages[MenuPage::ESP])
    {
        case SubPage::Players:
            ImGui::Columns(2, nullptr, false); {
                ImGui::PushFont(NULL, style.FontSizeBase * 1.5f);
                ImGui::Text("Player ESP");
                ImGui::Spacing();
                ImGui::PopFont();
            } ImGui::NextColumn(); {
                DRGui::CheckBox("Enable ESP", &settings.esp.Enable);
            }

            ImGui::Columns(3, nullptr, false); {
                ImGui::SetColumnWidth(0, totalWidth * (3.4f / 10.0f));
                ImGui::SetColumnWidth(1, totalWidth * (1.6f / 10.0f) - 8);

                DRGui::CheckBox("Players", &settings.esp.Players);
            } ImGui::NextColumn(); {
                DRGui::ColorEdit3("##1", settings.esp.PlayerEnemyColor);
            } ImGui::NextColumn(); ImGui::NextColumn(); {
                DRGui::CheckBox("Ally Players", &settings.esp.AllyPlayers);
            } ImGui::NextColumn(); {
                DRGui::ColorEdit3("##2", settings.esp.PlayerAllyColor);
            } ImGui::NextColumn(); ImGui::NextColumn(); {
                DRGui::CheckBox("Team Players", &settings.esp.TeamPlayers);
            } ImGui::NextColumn(); {
                DRGui::ColorEdit3("##3", settings.esp.PlayerTeamColor);
            } ImGui::NextColumn(); ImGui::NextColumn(); {
                DRGui::CheckBox("Sleeping Players", &settings.esp.Sleeping);
                DRGui::CheckBox("Dead Players", &settings.esp.Dead);
                ImGui::Spacing();
            } ImGui::NextColumn(); ImGui::NextColumn(); {
                ImGui::PushItemWidth(totalWidth / 3 + 20);
                DRGui::SliderFloat("ESP Scale", &settings.esp.Scale, 0.1f, 5.0f);
                ImGui::PopItemWidth();
            } ImGui::Columns(2, nullptr, false); {
                ImGui::GetWindowDrawList()->AddLine(
                    ImGui::GetCursorScreenPos(),
                    ImVec2(ImGui::GetCursorScreenPos().x + ImGui::GetColumnWidth() - style.WindowPadding.x * 2,
                           ImGui::GetCursorScreenPos().y + 1.0f),
                    ImGui::GetColorU32(ImGuiCol_Separator), 1.0f
                );

            } ImGui::NextColumn(); {

                ImGui::GetWindowDrawList()->AddLine(
                    ImGui::GetCursorScreenPos(),
                    ImVec2(ImGui::GetCursorScreenPos().x + ImGui::GetColumnWidth() - style.WindowPadding.x * 2,
                           ImGui::GetCursorScreenPos().y + 1.0f),
                    ImGui::GetColorU32(ImGuiCol_Separator), 1.0f
                );
            } ImGui::NextColumn(); {

                ImGui::Spacing();
                ImGui::Spacing();
                DRGui::CheckBox("HP Bar", &settings.esp.HPBar);
                ImGui::SameLine(100.f);
                DRGui::CheckBox("Armor", &settings.esp.Armor);
                DRGui::CheckBox("Tracers", &settings.esp.Tracers);
                ImGui::SameLine(100.f);
                DRGui::CheckBox("Weapon", &settings.esp.Weapon);
                //DRGui::CheckBox("Shots", &settings.esp.ShotTraces);
                //ImGui::SameLine(100.f);
                DRGui::CheckBox("Skeleton", &settings.esp.Skeleton);
                ImGui::SameLine(100.f);
                if (DRGui::CheckBox("3D Box", &settings.esp.Box3D))
                {
                    if (settings.esp.Box3D)
                        settings.esp.Box2D = false;
                }
                //ImGui::SameLine(100.f);
                if (DRGui::CheckBox("2D Box", &settings.esp.Box2D))
                {
                    if (settings.esp.Box2D)
                        settings.esp.Box3D = false;
                }
                ImGui::Spacing();

                ImGui::GetWindowDrawList()->AddLine(
                    ImGui::GetCursorScreenPos(),
                    ImVec2(ImGui::GetCursorScreenPos().x + ImGui::GetColumnWidth() - style.WindowPadding.x * 2,
                           ImGui::GetCursorScreenPos().y + 1.0f),
                    ImGui::GetColorU32(ImGuiCol_Separator), 1.0f
                );

            } ImGui::NextColumn(); {
                ImGui::Spacing();
                ImGui::Spacing();
                ImGui::PushFont(NULL, style.FontSizeBase * 1.5f);
                ImGui::Text("Self ESP");
                ImGui::Spacing();
                ImGui::PopFont();
                DRGui::CheckBox("Self Armor", &settings.SelfArmorESP);
                DRGui::CheckBox("Self Box 3D", &settings.Self3DBoxESP);
                DRGui::CheckBox("Self Skeleton", &settings.SelfBoneESP);
            }
            ImGui::Columns(1);
            break;
        case SubPage::Dinosaurs:
            ESPDinos(totalWidth);
            ImGui::Columns(1);
            break;
        case SubPage::Structures:
            ImGui::PushFont(NULL, style.FontSizeBase * 1.5f);
            ImGui::Text("Structures ESP");
            ImGui::Spacing();
            ImGui::PopFont();

            DRGui::CheckBox("Structures", &settings.esp.Structures);

            ImGui::Columns(4, nullptr, false); {
                ImGui::SetColumnWidth(0, (totalWidth / 2) * (2.0f / 3.0f));
                ImGui::SetColumnWidth(1, (totalWidth / 2) * (1.0f / 3.0f) - 8);
                ImGui::SetColumnWidth(2, (totalWidth / 2) * (2.0f / 3.0f));

                DRGui::CheckBox("Ally Structures", &settings.esp.AllyStructures);
            } ImGui::NextColumn();  {
                DRGui::ColorEdit3("##1", settings.esp.StructureAllyColor);
            } ImGui::NextColumn();  {
                DRGui::CheckBox("PlantX", &settings.esp.PlantX);
            } ImGui::NextColumn();  {
                DRGui::ColorEdit3("##7", settings.esp.PlantXColor);
            } ImGui::NextColumn();  {
                DRGui::CheckBox("Team Structures", &settings.esp.TeamStructures);
            } ImGui::NextColumn();  {
                DRGui::ColorEdit3("##2", settings.esp.StructureTeamColor);
            } ImGui::NextColumn();  {
                DRGui::CheckBox("Supply Crates", &settings.esp.SupplyCrate);
            } ImGui::NextColumn();  {
                DRGui::ColorEdit3("##8", settings.esp.SupplyCrateColor);
            } ImGui::NextColumn();  {
                DRGui::CheckBox("Containers", &settings.esp.Containers);
            } ImGui::NextColumn();  {
                DRGui::ColorEdit3("##3", settings.esp.ContainersColor);
            } ImGui::NextColumn();  {
                DRGui::CheckBox("Item Cache", &settings.esp.ItemCache);
            } ImGui::NextColumn();  {
                DRGui::ColorEdit3("##9", settings.esp.ItemCacheColor);
            } ImGui::NextColumn();  {
                DRGui::CheckBox("Beds", &settings.esp.Beds);
            } ImGui::NextColumn(); {
                DRGui::ColorEdit3("##4", settings.esp.BedsColor);
            } ImGui::Columns(3, nullptr, false); {
                ImGui::SetColumnWidth(0, (totalWidth / 2) * (2.0f / 3.0f));
                ImGui::SetColumnWidth(1, (totalWidth / 2) * (1.0f / 3.0f) - 8);
                DRGui::CheckBox("Explosives", &settings.esp.Explosives);
            }  ImGui::NextColumn(); {
                DRGui::ColorEdit3("##5", settings.esp.ExplosivesColor);
            }  ImGui::NextColumn(); ImGui::NextColumn(); {
                DRGui::CheckBox("Turrets", &settings.esp.Turrets);
            }  ImGui::NextColumn(); {
                DRGui::ColorEdit3("##6", settings.esp.TurretsColor);
            } ImGui::NextColumn(); {
                ImGui::PushItemWidth(totalWidth / 3 + 20);
                DRGui::SliderInt("Max Draw Distance", &settings.esp.MaxDistance, 0, 10000);
                ImGui::PopItemWidth();
            } ImGui::Columns(1);
            ImGui::Spacing();
            ImGui::Separator();
            ImGui::Spacing();
            DRGui::CheckBox("Include in hide draw", &settings.esp.HideStructureSwitch);
           //  DRGui::CheckBox("Hide Structure", &settings.esp.HideStructure);
            break;
        case SubPage::Other:
            ESPOthers(totalWidth);
            ImGui::Columns(1);
        default:
            break;
    }
}


#include "../DinoNames.h"


void UserMenu::ESPDinos(float totalWidth) {
    ExecutionTimer::Synchronize(204, true);

    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(1.0f, 6.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(1.0f, 1.0f));
    ImGui::BeginChild("DinosLeft", ImVec2(ShouldFilter ? totalWidth / 2 - 43 : totalWidth / 2 - 23, totalWidth / 2  - 5), ImGuiChildFlags_Borders, ImGuiWindowFlags_NoBackground);
    ImGui::PopStyleVar();
    {
        ImGui::PushFont(NULL, style.FontSizeBase * 1.5f);
        ImGui::Text("Dino ESP");
        ImGui::Spacing();
        ImGui::PopFont();

        ImGui::Columns(2, nullptr, false);
        ImGui::SetColumnWidth(0, totalWidth * (3.0f / 10.0f));
        ImGui::SetColumnWidth(1, totalWidth * (1.0f / 5.0f) - 8);

        DRGui::CheckBox("Dinosaurs", &settings.esp.Dinosaurs);
        ImGui::NextColumn(); { DRGui::ColorEdit3("##DinoEnemyColor", settings.esp.DinoEnemyColor); }

        ImGui::NextColumn(); { DRGui::CheckBox("Wild Dinos", &settings.esp.WildDino); }
        ImGui::NextColumn(); { DRGui::ColorEdit3("##DinoWildColor", settings.esp.DinoWildColor); }

        ImGui::NextColumn(); { DRGui::CheckBox("Ally Dinos", &settings.esp.AllyDino); }
        ImGui::NextColumn(); { DRGui::ColorEdit3("##DinoAllyColor", settings.esp.DinoAllyColor); }

        ImGui::NextColumn(); { DRGui::CheckBox("Team Dinos", &settings.esp.TeamDino); }
        ImGui::NextColumn(); { DRGui::ColorEdit3("##DinoTeamColor", settings.esp.DinoTeamColor); }

        ImGui::NextColumn();
        DRGui::CheckBox("Gender", &settings.esp.ShowDinoGender);
        DRGui::CheckBox("Extended Info", &settings.esp.ShowDinoInfo);
        DRGui::CheckBox("Eggs", &settings.esp.Eggs);

        ImGui::EndColumns();
    } ImGui::PopStyleVar();
    ImGui::EndChild(); {
        ImGui::SameLine();
        ImGui::BeginGroup();
        if (!ShouldFilter) {

                ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.f, ImGui::GetContentRegionAvail().y - 160.0f)); {
                    ImGui::Spacing();
                } ImGui::PopStyleVar();

                ImGui::Spacing();
                ImGui::PushItemWidth(totalWidth / 3 + 20);
                DRGui::SliderInt("Dino Min Level", &settings.esp.MinDinoLevel, 0, 500);
                ImGui::PopItemWidth();

        } else {

            DRGui::CheckBox("Dino Filtering", &settings.esp.UseDinoSearch);
              ImGui::SameLine();
              if (DRGui::Button("Go Back", ImVec2(-0.1f, 0))) {
                  ShouldFilter = false;
              }

              DRGui::InputTextStr("##DnSrch", ICON_FA_SEARCH "  Search", &searchDinoBuffer, -0.1f, ImGuiInputTextFlags_ReadOnly);


              if (ImGui::IsItemClicked() && !alertControllerFlag) {
                  alertControllerFlag = true;

                  ShowTextInputAlert<std::string>(
                                                  @"Search",
                                                  nullptr,
                                                  @"",
                                                  @"",
                                                  true,

                                                  [&](const std::string& enteredText) {
                                                      searchDinoBuffer = enteredText.c_str();
                                                      searchDinoBuffer.shrink_to_fit();
                                                      searchDinoBuffer.reserve(128);

                                                      searchDinoStrLower = ToLower(searchDinoBuffer);

                                                      alertControllerFlag = false;
                                                      currentDinoPage = 0;
                                                  },

                                                  [&](const std::string& ) {
                                                      alertControllerFlag = false;
                                                  }
                                                  );
              }


            using GroupMap = std::map<std::string, std::vector<int>>;
            std::vector<GroupMap::const_iterator> filteredGroups;
            filteredGroups.reserve(DinoNameGroups.size());

            if (searchDinoStrLower.empty())
            {
                for (auto it = DinoNameGroups.begin(); it != DinoNameGroups.end(); ++it)
                    filteredGroups.push_back(it);
            }
            else
            {
                for (auto it = DinoNameGroups.begin(); it != DinoNameGroups.end(); ++it)
                {
                    const std::string nameLower = ToLower(it->first);
                    if (nameLower.find(searchDinoStrLower) != std::string::npos)
                        filteredGroups.push_back(it);
                }
            }

            totalDinoFiltered = static_cast<uint16_t>(filteredGroups.size());

            uint16_t totalPages = (totalDinoFiltered + itemsPerPage - 1) / itemsPerPage;
            totalPages = totalPages > 0 ? 1u * totalPages : 1u;
            if (currentDinoPage >= static_cast<int>(totalPages)) currentDinoPage = static_cast<int>(totalPages) - 1;
            if (currentDinoPage < 0) currentDinoPage = 0;

            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(1, 14));
            ImGui::BeginChild("DnLst",
                              ImVec2(GroupWidth / 2, ImGui::GetContentRegionAvail().y - 50),
                              ImGuiChildFlags_Borders,
                              ImGuiWindowFlags_NoBackground);
            ImGui::PopStyleVar();
            {
                const uint16_t startIdx = static_cast<uint16_t>(currentDinoPage) * itemsPerPage;
                const uint16_t endIdx   = std::min<uint16_t>(startIdx + itemsPerPage, totalDinoFiltered);

                for (uint16_t j = startIdx; j < endIdx; ++j)
                {
                    const auto& entry   = *filteredGroups[j];
                    const std::string& Name    = entry.first;
                    const std::vector<int>& Indices = entry.second;

                    bool IsChecked = std::any_of(Indices.begin(), Indices.end(),
                                                 [&](int idx){ return settings.esp.AllDinosaurs[idx]; });

                    if (DRGui::CheckBox(Name.c_str(), &IsChecked))
                    {
                        for (int idx : Indices)
                            settings.esp.AllDinosaurs[idx] = IsChecked;
                    }
                }

                if (filteredGroups.empty())
                {
                    ImGui::TextColored(ImVec4(1,0,0,1), "No Match");
                }
            }
            ImGui::EndChild();

            if (currentDinoPage > 0) {
                if (DRGui::Button(ICON_FA_CARET_LEFT, ImVec2(65, 0))) currentDinoPage--;
            } else {
                ImGui::BeginDisabled();
                DRGui::Button(ICON_FA_CARET_LEFT, ImVec2(65, 0));
                ImGui::EndDisabled();
            }
            ImGui::SameLine();

            {
                std::string pageIndicator = fmt::format("{}/{}", totalDinoFiltered == 0 ? 0 : currentDinoPage + 1, totalPages);
                ImGui::Text("%s", pageIndicator.c_str());
            }

            ImGui::SameLine();
            if (currentDinoPage < static_cast<int>(totalPages) - 1) {
                if (DRGui::Button(ICON_FA_CARET_RIGHT, ImVec2(65, 0))) currentDinoPage++;
            } else {
                ImGui::BeginDisabled();
                DRGui::Button(ICON_FA_CARET_RIGHT, ImVec2(65, 0));
                ImGui::EndDisabled();
            }

        }
        ImGui::EndGroup();
    } ImGui::Columns(1);
    if (!ShouldFilter) {
        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();
        ImGui::Columns(2, nullptr, false);
        DRGui::CheckBox("Include in hide draw", &settings.esp.HideDinosaurSwitch);
       //  DRGui::CheckBox("Hide Dinosaur", &settings.esp.HideDinosaur);
        ImGui::NextColumn();
        if (DRGui::Button("Filter Dino", ImVec2(totalWidth / 3 + 20, 0))) {
            ShouldFilter = true;
        }
    }
}


void UserMenu::ESPOthers(float totalWidth) {

    bool isEnabled = settings.g_CrosshairSettings.cross_enabled || settings.g_CrosshairSettings.small_circle_enabled || settings.g_CrosshairSettings.small_dot_enabled;

    switch(menuState.subSubPages[SubPage::Other]) {
        case SubSubPage::Resources:
            ImGui::Columns(3, nullptr, false); {
                ImGui::SetColumnWidth(0, totalWidth * (3.0f / 10.0f));
                ImGui::SetColumnWidth(1, totalWidth * (1.0f / 5.0f) - 8);
                DRGui::CheckBox("Resources", &settings.esp.Resources);
                DRGui::CheckBox("Metal", &settings.esp.Metal);
                DRGui::CheckBox("Oil", &settings.esp.Oil);
                DRGui::CheckBox("Obsidian", &settings.esp.Obsidian);
            } ImGui::NextColumn(); {
                DRGui::ColorEdit3("##1", settings.esp.ResourceColor);
            } ImGui::NextColumn(); {
                DRGui::CheckBox("Perls", &settings.esp.Perl);
                DRGui::CheckBox("Crystal", &settings.esp.Crystal);
                DRGui::CheckBox("Explorer Note", &settings.esp.ExplorerNotes);
                // DRGui::CheckBox("Eggs", &settings.esp.Eggs);

            } ImGui::Columns(2, nullptr, false);
            ImGui::Spacing();

            ImGui::GetWindowDrawList()->AddLine(
                                                ImGui::GetCursorScreenPos(),
                                                ImVec2(ImGui::GetCursorScreenPos().x + ImGui::GetColumnWidth() - style.WindowPadding.x * 2,
                                                       ImGui::GetCursorScreenPos().y + 1.0f),
                                                ImGui::GetColorU32(ImGuiCol_Separator), 1.0f
                                                );

            ImGui::Spacing();
            ImGui::Spacing();
            DRGui::CheckBox("Include in hide draw", &settings.esp.HideResourceSwitch);
            // DRGui::CheckBox("Hide Resource", &settings.esp.HideResource);
            return;
        case SubSubPage::Crosshair:
            ImGui::Columns(3, nullptr, false); {
                ImGui::SetColumnWidth(0, totalWidth * (3.0f / 10.0f));
                ImGui::SetColumnWidth(1, totalWidth * (1.0f / 5.0f) - 8);

                DRGui::CheckBox("   Use Cross", &settings.g_CrosshairSettings.cross_enabled);

                if (isEnabled) {
                    DRGui::CheckBox("   Outline", &settings.g_CrosshairSettings.outline_cross);
                } else {
                    settings.g_CrosshairSettings.outline_cross = false;
                }


            } ImGui::NextColumn(); {
                DRGui::ColorEdit3("##jjj", (float*)&settings.g_CrosshairSettings.color);
                if (isEnabled) {
                    DRGui::ColorEdit3("##cc", (float*)&settings.g_CrosshairSettings.outline_color);
                }
            } ImGui::NextColumn(); {
                static const char current_[] = "Four Sticks\0Four Sticks 45°\0Three Sticks\0Triangle\0";
                DRGui::ArrowSelector("CrosshairType",  &(int&)settings.g_CrosshairSettings.type, current_, ImVec2(150.0f, 0.0f), false);

                ImGui::Spacing();

            } ImGui::Columns(2, nullptr, false); {

                if (isEnabled) {
                    DRGui::CheckBox("   Make Foreground", &settings.g_CrosshairSettings.make_foreground);
                }

                ImGui::PushItemWidth(totalWidth / 3 - 20);
                DRGui::CheckBox("##1", &settings.g_CrosshairSettings.small_circle_enabled);
                ImGui::SameLine();
                DRGui::SliderFloat("Circle Sight", &settings.g_CrosshairSettings.small_circle_radius, 0.5f, 10.0f);

                DRGui::CheckBox("##2", &settings.g_CrosshairSettings.small_dot_enabled);
                ImGui::SameLine();
                DRGui::SliderFloat("Dot", &settings.g_CrosshairSettings.small_dot_radius, 0.1f, 3.0f);
                ImGui::PopItemWidth();

            } ImGui::NextColumn(); {

                ImGui::PushItemWidth(totalWidth / 3 + 20);
                if (isEnabled) {
                    DRGui::SliderFloat("Thickness", &settings.g_CrosshairSettings.thickness, 0.0f, 0.7f);
                }


                DRGui::SliderFloat("Size", &settings.g_CrosshairSettings.size, 1.4f, 15.0f);
                DRGui::SliderFloat("Gap", &settings.g_CrosshairSettings.gap, 0.0f, 10.0f);

                ImGui::PopItemWidth();
            }
            return;
        case SubSubPage::Map:
            ImGui::Columns(3, nullptr, false); {
                ImGui::SetColumnWidth(0, totalWidth * (3.0f / 10.0f));
                ImGui::SetColumnWidth(1, totalWidth * (1.0f / 5.0f) - 8);

                if (DRGui::CheckBox("Use Map", &settings.MapEnabled) && !settings.MapEnabled) {
                    Map::DestroyInstance();
                }
            } ImGui::NextColumn(); {
                DRGui::ColorEdit4("##rrrf", (float*)&settings.MapSetting.MapColor);

            } ImGui::NextColumn(); {
                ImGui::PushItemWidth(totalWidth / 3 + 20);
                DRGui::SliderFloat("Map Size", &settings.MapSetting.MapSize, 50, 350);
                ImGui::PopItemWidth();
            } ImGui::Columns(2, nullptr, false); {
                DRGui::CheckBox("Enable Day Time Mode", &settings.MapSetting.bDayTimeMode);
                // DRGui::SliderFloat("Simulate Day Time", &settings.MapSetting.fDayTime, 0, 24);
            } ImGui::NextColumn(); {
                ImGui::PushItemWidth(totalWidth / 3 + 20);
                DRGui::SliderInt("Map Zoom", &settings.MapSetting.MapZoom, 1, 10);
                ImGui::PopItemWidth();
            }

//            if (DRGui::SliderInt("Map Transparency", &settings.MapSetting.MapTransparency, 0, 255)) {
//                settings.MapSetting.MapColor.Value.w = (float)settings.MapSetting.MapTransparency * (1.0f / 255.0f);
//            }

            return;
        default:
            return;
    }
}

/* * * * * * ESP Header End * * * * * */


#pragma mark - Misc Header -

/* * * * * * * * * * * * * * * * * * * * * * */
/* * * * * * * Misc Header Begin * * * * * * */
/* * * * * * * * * * * * * * * * * * * * * * */
void UserMenu::MiscHeader()
{
    // ImGui::Spacing();
    switch (menuState.subPages[MenuPage::Misc])
    {
        case SubPage::Misc:
        {
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(14.0f, 2.0f));
            ImGui::Columns(2, nullptr, false);
            if (DRGui::Button("Unlock Notes", ImVec2(-1,0)))
            {
                ShooterPlayerControllerQueue.Add(UnlockNotes);
            }
            ImGui::NextColumn();
            if (DRGui::Button("Unlock Admin", ImVec2(-1,0)))
            {
                ShooterPlayerControllerQueue.Add(UnlockAdmin);
            }
            ImGui::NextColumn();
            if (DRGui::Button("Enter Dungeon", ImVec2(-1,0)))
            {
                ShooterPlayerControllerQueue.Add(EnterDungeon);
            }
            ImGui::NextColumn();
            if (DRGui::Button("Suicide", ImVec2(-1,0)))
            {
                ShooterPlayerControllerQueue.Add(Suicide);
            }
            ImGui::NextColumn();
            if (DRGui::Button("Rollback", ImVec2(-1,0)))
            {
                ShooterPlayerControllerQueue.Add(Rollback);
            }
            ImGui::NextColumn();
            if (DRGui::Button("Dungeon Menu", ImVec2(-1,0)))
            {
                ShooterPlayerControllerQueue.Add(DungeonMenu);
            }
            ImGui::NextColumn();
            if (DRGui::Button("Resurrect Dino", ImVec2(-1,0)))
            {
                ShooterPlayerControllerQueue.Add(ResurrectDino);
            }
            ImGui::NextColumn();
            if (DRGui::Button("Transfer From Container", ImVec2(-1,0)))
            {
                ShooterPlayerControllerQueue.Add(TransferFromContainer);
            }
            ImGui::NextColumn();
            if (DRGui::Button("Transfer To Container", ImVec2(-1,0)))
            {
                ShooterPlayerControllerQueue.Add(TransferToContainer);
            }
            ImGui::NextColumn();
            if (DRGui::Button("Claim Targeted Dino", ImVec2(-1,0)))
            {
                ShooterPlayerControllerQueue.Add(ClaimTargetedDino);
            }
            ImGui::NextColumn();
            if (DRGui::Button("Pickup Targeted Structure", ImVec2(-1,0)))
            {
                ShooterPlayerControllerQueue.Add(PickupTargetedStructure);
            }
            ImGui::NextColumn();
            if (DRGui::Button("Random Teleport", ImVec2(-1,0)))
            {
                ShooterPlayerControllerQueue.Add(RandomTeleport);
            }
            ImGui::NextColumn();
            if (DRGui::Button("Relog", ImVec2(-1,0)))
            {
                ShooterPlayerControllerQueue.Add(Relog);
            }
            ImGui::NextColumn();
            if (DRGui::Button("Quit To Menu", ImVec2(-1,0)))
            {
                ShooterPlayerControllerQueue.Add(QuitToMenu);
            }
            ImGui::NextColumn();
            if (DRGui::Button("Glitch Dimension", ImVec2(-1,0)))
            {
                ShooterPlayerControllerQueue.Add(RemoveDungeonLoadingScreen);
            }
            ImGui::NextColumn();
            if (DRGui::Button("Claim All Dinos", ImVec2(-1,0)))
            {
                ShooterPlayerControllerQueue.Add(ClaimAllDinos);
            }
            ImGui::NextColumn();
            if (DRGui::Button("Pickup All Structures", ImVec2(-1,0)))
            {
                ShooterPlayerControllerQueue.Add(PickupAllStructures);
            }
            ImGui::NextColumn();
            if (DRGui::Button("Set Light Mode", ImVec2(-1,0)))
            {
                static std::vector<std::string> LightOptions = {"Dungeon", "World", "Arena"};
                iOS::ShowSelectionAlert(@"Choose a light mode", @"", LightOptions, [](int Index) {
                    SetLightType(Index);
                });
            }
            ImGui::NextColumn();
            if (DRGui::Button("Send Message", ImVec2(-1,0)))
            {
                static std::vector<std::string> MessageOptions = {"Normal", "Announcement", "Notification", "Login", "Emote"};

                auto OutStr = std::make_shared<std::wstring>();
                iOS::ShowTextInputAlert(@"", @"Type Message here", *OutStr, [OutStr](bool Success) {
                    if (!Success) return;

                    iOS::ShowSelectionAlert(@"Choose a message type", @"", MessageOptions, [OutStr](int Index) {
                        SendMessage(*OutStr, Index);
                    });
                });
            }
            ImGui::NextColumn();
            //            if (DRGui::Button("Debug", ImVec2(-1,0)))
            //            {
            //                ShooterPlayerControllerQueue.Add([](auto* PC) { DumpAllBlueprintIDs(); });
            //            }


            ImGui::EndColumns();
            ImGui::PopStyleVar();
        }
            return;
        case SubPage::Weapon:
        {
            ImGui::Columns(2, nullptr, false);
            DRGui::CheckBox("Tame Shooting", &settings.TameShooting);
            ImGui::NextColumn();
            DRGui::CheckBox("No Scope Sway", &settings.NoScopeSway);
            ImGui::NextColumn();
            DRGui::CheckBox("360 Mounted Weaponry", &settings.UnlockRotation);
            ImGui::NextColumn();
            DRGui::CheckBox("No Spread", &settings.NoSpread);
            ImGui::NextColumn();
            DRGui::CheckBox("No TekRifle Overheat", &settings.NoTekRifleOverheat);
            ImGui::NextColumn();
            DRGui::CheckBox("Submerged Firing", &settings.SubmergedFiring);
            ImGui::NextColumn();
            DRGui::CheckBox("Bullet Burst", &settings.BulletBurst);
            ImGui::NextColumn();
            DRGui::CheckBox("No Scope Overlay", &settings.NoScopeOverlay);
            ImGui::NextColumn();
            DRGui::CheckBox("Inf Fabi Pistol Ammo", &settings.InfFabiPistolAmmo);
            ImGui::NextColumn();
            DRGui::CheckBox("Inf Projectile", &settings.ProjectileSpam);
            ImGui::NextColumn();
            DRGui::CheckBox("Inf Ballista Projectiles", &settings.BallistaSpam);
            ImGui::NextColumn();
            DRGui::CheckBox("Big Gun", &settings.BigGun);
            ImGui::NextColumn();
            DRGui::CheckBox("Infinite C4", &settings.InfiniteC4);
            ImGui::NextColumn();
            DRGui::CheckBox("No Shotgun Reload", &settings.NoReloadShotgun);
            ImGui::EndColumns();
            ImGui::Spacing();
            ImGui::Separator();
        }
            return;

        case SubPage::Personal:
        {
            ImGui::PushFont(NULL, style.FontSizeBase * 1.5f);
            ImGui::Text("Player");
            ImGui::PopFont();

            ImGui::Columns(2, nullptr, false);
            DRGui::CheckBox("Ghost Mode", &settings.GhostMode);
            ImGui::NextColumn();
            DRGui::CheckBox("Show Floating Damage", &settings.ShowFloatingDamage);
            ImGui::NextColumn();
            DRGui::CheckBox("Instant Respawn", &settings.NoSpawnAnim);
            ImGui::NextColumn();
            DRGui::CheckBox("Freeze", &settings.ShowFreezeSwitch);
            ImGui::NextColumn();
            DRGui::CheckBox("Self Explosions", &settings.AutoExplosions);
            ImGui::NextColumn();
            DRGui::CheckBox("Hide Login", &settings.HideLogin);
            ImGui::NextColumn();
            DRGui::CheckBox("Join Notifications", &settings.JoinNotifications);
            ImGui::NextColumn();
            DRGui::CheckBox("Tap To Bed Teleport", &settings.TapToBedTeleport);
            ImGui::NextColumn();
            DRGui::CheckBox("No Knockout Blur", &settings.NoKnockoutBlur);
            ImGui::NextColumn();
            DRGui::CheckBox("Fake Primal Pass", &settings.FakePrimal);
            ImGui::NextColumn();
            DRGui::CheckBox("Chat Spam", &settings.ChatSpam);
            ImGui::EndColumns();
            ImGui::Spacing();
            ImGui::Separator();
            ImGui::Spacing();
            ImGui::PushFont(NULL, style.FontSizeBase * 1.5f);
            ImGui::Text("Dino");
            ImGui::PopFont();

            ImGui::Columns(2, nullptr, false);

            DRGui::CheckBox("Instant Turn", &settings.InstantTurn);
            ImGui::NextColumn();
            DRGui::CheckBox("Quick Turn", &settings.QuickTurn);
            ImGui::NextColumn();
            DRGui::CheckBox("Flyer Strafing", &settings.Strafing);
            ImGui::NextColumn();
            DRGui::CheckBox("Auto Healing", &settings.HealDinosaur);
            ImGui::NextColumn();
            DRGui::CheckBox("Auto Grab Players", &settings.AutoGrabPlayers);
            ImGui::EndColumns();
        }
            return;

        case SubPage::Automation:
        {
            ImGui::Columns(2, nullptr, false);
            DRGui::CheckBox("Auto Armor", &settings.AutoArmor);
            ImGui::NextColumn();
            DRGui::CheckBox("Auto Meds", &settings.AutoMeds);
            ImGui::NextColumn();
            DRGui::CheckBox("Auto Stamina", &settings.AutoStamina);
            ImGui::NextColumn();
            DRGui::CheckBox("Auto Demo Target", &settings.AutoDestroyBot);
            ImGui::EndColumns();
            ImGui::Spacing();
            ImGui::Separator();
            ImGui::Spacing();

            ImGui::PushFont(NULL, style.FontSizeBase * 1.5f);
            const auto& SubSubPageNames = EnumNameCache::GetInstance().GetSubSubPageNames();
            DRGui::RadioFrameText(SubSubPageNames.at(SubSubPage::Auto_Loot), reinterpret_cast<int*>(&menuState.subSubPages[SubPage::Automation]), static_cast<int>(SubSubPage::Auto_Loot));
            ImGui::SameLine();
            DRGui::CheckBox("##1Enable", &settings.AutoSteal);
            ImGui::SameLine();
            DRGui::RadioFrameText(SubSubPageNames.at(SubSubPage::Auto_Drop_Items), reinterpret_cast<int*>(&menuState.subSubPages[SubPage::Automation]), static_cast<int>(SubSubPage::Auto_Drop_Items));
            ImGui::SameLine();
            DRGui::CheckBox("##2Enable", &settings.AutoDropItems);
            ImGui::PopFont();

            ImGui::Spacing();
            ImGui::Separator();
            ImGui::Spacing();

            if (menuState.subSubPages[SubPage::Automation] == SubSubPage::Auto_Loot) {

                ImGui::BeginDisabled(!settings.AutoSteal);
                DRGui::CheckBox("Players", &settings.LootPlayers);
                DRGui::CheckBox("Turrets", &settings.LootTurrets);
                DRGui::CheckBox("Supply Crates", &settings.LootSupplyCrates);
                DRGui::CheckBox("Containers", &settings.LootContainers);
                ImGui::EndDisabled();
            } else {
                ImGui::BeginDisabled(!settings.AutoDropItems);
                DRGui::InputTextStr("##UnifiedSearch", ICON_FA_SEARCH "  Filter all lists...", &unifiedFilter, -1.0f, ImGuiInputTextFlags_ReadOnly);


                if (ImGui::IsItemClicked() && !alertControllerFlag) {
                    alertControllerFlag = true;

                    ShowTextInputAlert<std::string>(
                                                    @"Search",
                                                    nullptr,
                                                    @"",
                                                    @"",
                                                    true,

                                                    [&](const std::string& enteredText) {
                                                        unifiedFilter = enteredText.c_str();
                                                        unifiedFilter.shrink_to_fit();
                                                        unifiedFilter.reserve(128);
                                                        alertControllerFlag = false;
                                                    },

                                                    [&](const std::string& ) {
                                                        alertControllerFlag = false;
                                                    }
                                                    );
                }

                const ImGuiStyle& style = ImGui::GetStyle();
                const float spacing      = style.ItemSpacing.x;
                const float totalW       = ImGui::GetContentRegionAvail().x;
                const float childW       = (totalW - 2.0f * spacing) / 3.0f;
                const float childH       = ImGui::GetContentRegionAvail().y;

                const std::string filterLower = ToLower(unifiedFilter);

                auto RenderFilterPane = [&](const char* paneTitle,
                                            int& currentIndex,
                                            const std::vector<const char*>& names,
                                            ImVec2 size)
                {
                    if (!names.empty()) {
                        if (currentIndex < 0) currentIndex = 0;
                        if (currentIndex >= (int)names.size()) currentIndex = (int)names.size() - 1;
                    } else {
                        currentIndex = -1;
                    }


                    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(1.0f, 1.0f));
                    ImGui::BeginChild(paneTitle, ImVec2(size.x + 6, size.y - 20), ImGuiChildFlags_Borders, ImGuiWindowFlags_NoBackground);
                    ImGui::PopStyleVar();
                    {
                        // Header
                        ImGui::TextUnformatted(paneTitle);
                        ImGui::Separator();

                        int shown = 0;

                        for (int i = 0; i < (int)names.size(); ++i)
                        {
                            const char* raw = names[i] ? names[i] : "";
                            const std::string nameStr(raw);
                            const std::string nameLower = ToLower(nameStr);

                            if (!filterLower.empty() && nameLower.find(filterLower) == std::string::npos)
                                continue;

                            ++shown;
                            const bool selected = (i == currentIndex);

                            // Full-width row
                            if (ImGui::Selectable(raw, selected, ImGuiSelectableFlags_AllowDoubleClick, ImVec2(0, 0))) {
                                currentIndex = i;
                            }

                            if (selected)
                                ImGui::SetItemDefaultFocus();
                        }

                        if (names.empty()) {
                            ImGui::TextDisabled("No items");
                        } else if (shown == 0) {
                            ImGui::TextDisabled("No match");
                        }
                    }
                    ImGui::EndChild();

                };

                ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(3.0f, 6.0f));
                RenderFilterPane("Item Types",        settings.ItemTypeFilter,        ItemTypeNames,        ImVec2(childW, childH));
                ImGui::SameLine();
                RenderFilterPane("Equipment Types",   settings.EquipmentTypeFilter,   EquipmentTypeNames,   ImVec2(childW, childH));
                ImGui::SameLine();
                RenderFilterPane("Consumables",       settings.ConsumableTypeFilter,  ConsumableTypeNames,  ImVec2(childW, childH));
                ImGui::PopStyleVar();
                ImGui::EndDisabled();
            }
        }   return;

        default:
            return;
    }
}
/* * * * * * Misc Header End * * * * * * * * */

#pragma mark - AimBot Header -

/* * * * * * * * * * * * * * * * * * * * * * */
/* * * * * *  AimBot Header Begin  * * * * * */
/* * * * * * * * * * * * * * * * * * * * * * */

void UserMenu::AimBotHeader()
{
    ExecutionTimer::Synchronize(205, false);

    DRGui::CheckBox("Enable", &settings.EnableAimbot);
    if (settings.EnableAimbot) {
        ImGui::SameLine();
        ImGui::Dummy(ImVec2(SideBarWidth / 3, 0));
        ImGui::SameLine();
        DRGui::CheckBox("##AimFov" , &settings.UseAimFOV);
        ImGui::SameLine();
        ImGui::PushItemWidth((size.x - SideBarWidth) / 2 - 15);
        DRGui::SliderInt("Aim FOV", &settings.AimFOVRadius, 50, 500);
        ImGui::PopItemWidth();
    } else ImGui::Spacing();
    ImGui::BeginDisabled(!settings.EnableAimbot); {
        ImGui::Separator();
        ImGui::Spacing();
        ImGui::Columns(2, 0, false); {
            DRGui::CheckBox("Smart Aimbot", &settings.AimAtWeakestArmor);
            DRGui::CheckBox("Triggerbot", &settings.ShowAutoFireSwitch);
            DRGui::CheckBox("Bow Aimbot", &settings.BowAimbot);
            ImGui::BeginDisabled(!settings.AimType);
            if (!settings.AimType) { settings.CrashPlayersAim = false; settings.ShieldBypass = false; }
            DRGui::CheckBox("Bypass Shield", &settings.ShieldBypass);
            DRGui::CheckBox("Crash Silent Aim", &settings.CrashPlayersAim);
            ImGui::EndDisabled();
            DRGui::CheckBox("Ragebot" , &settings.Ragebot);
        } ImGui::NextColumn(); {
            static const char kAims[] = "Hard Lock\0Silent Aim\0";
            DRGui::ArrowSelector("Aim Type", &settings.AimType, kAims, ImVec2(150.0f, 0.0f), false);
            static const char kBones[] = "Head\0Chest\0Arms\0Legs\0";
            DRGui::ArrowSelector("Aim Location", &settings.AimTargetIndex, kBones, ImVec2(150.0f, 0.0f), false);
            ImGui::Spacing();
            DRGui::CheckBox("Slow Dinos" , &settings.SlowDinosAimbot);
        } ImGui::Columns(1, 0, false);
        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();
    } ImGui::EndDisabled();

    // ImGui::Spacing(); ImGui::SameLine();
    ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 208, 0, 255));
    ImGui::Text("  " ICON_FA_INFO);
    ImGui::PopStyleColor();

    if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayShort | ImGuiHoveredFlags_NoSharedDelay))
    {
        ImGui::SameLine();
        ImGui::TextDisabled(
            "*Hard Lock - Your crosshair locks onto enemies \n"
            "*Silent Aim - Your crosshair does not lock onto enemies \n"
            "*Bypass Shield - Shoots through shields\n"
            "*Smart Aimbot - Chooses weakest armor part to aim at\n"
            "*Triggerbot - Automatically shoots when enemy in sight \n"
            "*Crash Silent Aim - Makes the enemy crash on shot\n"
            "*Ragebot - Go crazy, spin crazy, become IMMORTAL\n"
        );
    }
}


/* * * * * *  AimBot Header End   * * * * * */


#pragma mark - Build Header -

/* * * * * * * * * * * * * * * * * * * * * * */
/* * * * * *  Build Header Begin   * * * * * */
/* * * * * * * * * * * * * * * * * * * * * * */


void UserMenu::BuildHeader()
{
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(9, 6));
    if (menuState.subPages[MenuPage::Structures] != SubPage::Turrets) {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(1, 1));
        ImGui::BeginChild("bg1", ImVec2(GroupWidth / 2,  GroupHeight), ImGuiChildFlags_Borders, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground);
        ImGui::PopStyleVar(1);
        {
            DRGui::CheckBox("Toggle Dupe", &settings.PlacementDupe);

            DRGui::CheckBox("Custom Structure", &settings.CustomPlacement);

            ImGui::Spacing();
            ImGui::Separator();
            ImGui::Spacing();

            DRGui::CheckBox("Floating Structures", &settings.FloatingStructures);
            //   DRGui::CheckBox("Floater", &settings.Floater);

            //   DRGui::CheckBox("Rotation", &settings.StructureFlip);

            //   DRGui::SliderFloat("Rotation Angle", &settings.FlipAngle, 0.0f, 360.0f, -0.1f);
            ImGui::Spacing();
            ImGui::Separator();
            ImGui::Spacing();
            DRGui::CheckBox("Structure Flip", &settings.StructureFlip);

            if (settings.StructureFlip)
            {
                ImGui::PushItemWidth(ImGui::GetWindowWidth() - 2);
                DRGui::SliderFloat("Pitch", &settings.FlipPitch, 0.f, 360.0f);
                DRGui::SliderFloat("Yaw", &settings.FlipYaw, 0.f, 360.0f);
                DRGui::SliderFloat("Roll", &settings.FlipRoll, 0.f, 360.0f);
                ImGui::PopItemWidth();
            }
        } ImGui::EndChild();
        ImGui::SameLine();

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(6, 1));

        ImGui::BeginGroup(); {
            ImGui::BeginChild("bg4", ImVec2(0, GroupHeight / 9.5), ImGuiChildFlags_Borders, ImGuiWindowFlags_NoBackground); // ImGuiWindowFlags_MenuBar |
            {

                DRGui::InputTextStr("##BldSrch", ICON_FA_FILTER "  Search", &searchBuildBuffer, ImGui::GetWindowWidth() - style.ScrollbarSize - style.WindowPadding.x * 2, ImGuiInputTextFlags_ReadOnly);

                if (ImGui::IsItemClicked() && !alertControllerFlag) {
                    alertControllerFlag = true;

                    ShowTextInputAlert<std::string>(
                                                    @"Search",
                                                    nil,
                                                    @"",
                                                    @"",
                                                    true,

                                                    [&](const std::string& enteredText) {
                                                        searchBuildBuffer = enteredText.c_str();
                                                        searchBuildBuffer.shrink_to_fit();
                                                        searchBuildBuffer.reserve(128);

                                                        alertControllerFlag = false;
                                                    },

                                                    [&](const std::string& /*unused*/) {
                                                        alertControllerFlag = false;
                                                    }
                                                    );
                } //ImGui::Separator();


            } ImGui::EndChild();
            ImGui::PopStyleVar();

            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(6, 14));
            ImGui::BeginChild("bg3", ImVec2(0, 9 * GroupHeight / 10), ImGuiChildFlags_Borders, ImGuiWindowFlags_NoBackground); // ImGuiWindowFlags_MenuBar |
            {
                /* if (ImGui::BeginMenuBar()) {
                 ImGui::TextDisabled("Structure Index %i", settings.CurrentStructureID);
                 ImGui::EndMenuBar();
                 } */

                //ImGui::Columns(2, nullptr, false);

                auto BuildButton = [&](const char* label, uint16_t structId) {
                    if (searchBuildBuffer.empty() || ToLower(label).find(ToLower(searchBuildBuffer)) != std::string::npos) {
                        if (DRGui::Button(label, ImVec2(-0.1f, 0))) {
                            settings.PlacingStructureIndex = structId;
                        }
                        //  ImGui::NextColumn();
                    }
                };

                switch (menuState.subPages[MenuPage::Structures]) {
                    case SubPage::Regular: // Regular

                        BuildButton("Chemistry Bench", 16);
                        BuildButton("Indus Cooker", 31);
                        BuildButton("Indus Forge", 34);
                        BuildButton("Fabricator", 90);
                        BuildButton("Fridge", 103);
                        BuildButton("Air Conditioner", 104);
                        BuildButton("Generator", 106);
                        BuildButton("Straight Wire", 107);
                        BuildButton("Cross Wire", 189);
                        BuildButton("Slope Wire", 190);
                        BuildButton("Vertical Wire", 191);
                        BuildButton("Outlet", 108);
                        BuildButton("Omnidirectional Lamp", 217);
                        BuildButton("Smithy", 131);
                        BuildButton("Mortar Pestle", 153);
                        BuildButton("Indus Grill", 218);
                        BuildButton("Bunk Bed", 32);
                        BuildButton("Elegant Bed", 232);
                        BuildButton("Sleeping Bag", 168);
                        BuildButton("Revival Platform", 343);
                        BuildButton("Vault", 207);
                        BuildButton("Underwater Bomb", 36);
                        BuildButton("Plant Species X", 67);
                        BuildButton("Auto Turret", 102);
                        BuildButton("Eerie Turret", 292);
                        BuildButton("Narcotic Trap", 210);
                        BuildButton("Small Bear Trap", 219);
                        BuildButton("Large Bear Trap", 220);
                        BuildButton("Catapult", 222);
                        BuildButton("Rocket Mount", 224);

                        break;
                    case SubPage::Metal: // Metal

                        BuildButton("SignPost", 84);
                        BuildButton("Pillar", 184);
                        BuildButton("Foundation", 94);
                        BuildButton("Wall", 95);
                        BuildButton("Ceiling", 96);
                        BuildButton("Doorframe", 98);
                        BuildButton("Door", 97);
                        BuildButton("Dino Gate", 88);
                        BuildButton("Dino Door", 89);
                        BuildButton("Spike", 157);
                        BuildButton("Behemoth Door", 181);
                        BuildButton("Behemoth Gate", 182);
                        BuildButton("Sign", 200);
                        BuildButton("Curved Battlement", 300);
                        BuildButton("Battlement", 301);
                        BuildButton("Staircase", 7);
                        BuildButton("Tree Platform", 12);
                        BuildButton("Railing", 40);
                        BuildButton("Ladder", 183);
                        BuildButton("Pitched Roof", 55);
                        BuildButton("Slope Wall", 179);
                        BuildButton("Left Sloping Wall", 56);
                        BuildButton("Right Sloping Wall", 57);
                        BuildButton("Window Door", 174);
                        BuildButton("Window Frame", 175);
                        BuildButton("Fence Foundation", 179);
                        BuildButton("Water Pipe", 193);
                        BuildButton("Crossed Pipe", 194);
                        BuildButton("Horizontal Pipe", 195);
                        BuildButton("Inclined Pipe", 196);
                        BuildButton("Verticle Pipe", 197);
                        BuildButton("Water Crane", 198);

                        break;
                    case SubPage::Tek: // Tek

                        BuildButton("Window", 303);
                        BuildButton("Hatch Frame", 304);
                        BuildButton("Window Frame", 305);
                        BuildButton("Foundation", 306);
                        BuildButton("Door", 307);
                        BuildButton("Door Frame", 308);
                        BuildButton("Ceiling", 309);
                        BuildButton("Roof", 310);
                        BuildButton("Rail", 311);
                        BuildButton("Fence Foundation", 312);
                        BuildButton("Fence", 313);
                        BuildButton("Sloped Wall Right", 314);
                        BuildButton("Sloped Wall Left", 315);
                        BuildButton("Stair Case", 316);
                        BuildButton("Ladder", 317);
                        BuildButton("Ramp", 318);
                        BuildButton("Pillar", 319);
                        BuildButton("Hatch", 320);
                        BuildButton("Wall", 322);
                        BuildButton("Replicator", 323);
                        BuildButton("Implant Chamber", 324);
                        BuildButton("Feeding Trough", 325);
                        BuildButton("Generator", 326);
                        BuildButton("Bed", 327);
                        BuildButton("Kibble", 328);
                        BuildButton("Teleport", 329);
                        BuildButton("Light", 330);

                        break;
                    case SubPage::Premium: // Premium

                        BuildButton("Small MailBox", 228);
                        BuildButton("Metal MailBox", 229);
                        BuildButton("Mail Exchange", 230);
                        BuildButton("Green Light", 231);
                        BuildButton("Loot Box", 336);
                        BuildButton("Thatch Box", 337);
                        BuildButton("Wood Box", 338);
                        BuildButton("Stone Box", 339);
                        BuildButton("Metal Box", 340);
                        BuildButton("Random Box", 342);
                        BuildButton("Lumber Mill", 344);
                        BuildButton("Outpost", 345);
                        BuildButton("Chef Station", 346);
                        BuildButton("Factory", 347);
                        BuildButton("Loading Bench", 348);
                        BuildButton("Metal Foundry", 349);
                        BuildButton("Stone WorkShop", 350);
                        BuildButton("Tannery", 351);
                        BuildButton("Dye Studio", 352);
                        BuildButton("Toliet Paper", 353);
                        BuildButton("Carno Statue", 275);
                        BuildButton("Giga Statue", 276);
                        BuildButton("Penguin Statue", 277);
                        BuildButton("Pt Statue", 278);
                        BuildButton("Spino Statue", 279);
                        BuildButton("Tuso Statue", 280);
                        BuildButton("Equus Statue", 299);
                        BuildButton("Anky Statue", 332);
                        BuildButton("Racing Flag", 302);
                        BuildButton("Panel Flag", 92);
                        BuildButton("Spider Flag", 82);
                        BuildButton("Dragon Flag", 14);
                        BuildButton("Gorilla Flag", 15);

                        break;
                    default:
                        break;
                }// ImGui::Columns(1);

            } ImGui::EndChild();
        } ImGui::EndGroup();
    }   else {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(1, 1));
        ImGui::BeginChild("bg6", ImVec2(0,  GroupHeight), ImGuiChildFlags_Borders, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground);
        {
            DRGui::CheckBox("Turret Settings", &settings.EnableTurretSettings);

            ImGui::BeginDisabled(!settings.EnableTurretSettings);

            ImGui::Spacing();
            ImGui::Separator();
            ImGui::Spacing();

            DRGui::CheckBox("Auto Activate", &settings.AutoActivateTurrets);

            DRGui::CheckBox("Auto Name As Location", &settings.AutoNameTurrets);


            DRGui::CheckBox("Auto Range Settings", &settings.AutoRangeSettings);
            ImGui::SameLine();
            static const char RangeNames[] = "Low\0Medium\0High\0";
            DRGui::ArrowSelector("Range", &settings.CurrentRangeSetting, RangeNames, ImVec2(ImGui::GetWindowWidth() / 2, 0.0f), false);

            DRGui::CheckBox("Auto Target Settings", &settings.AutoTargetSettings);
            ImGui::SameLine();
            static const char TargetNames[] = "All Targets\0Survivors or Tamed\0Survivors\0Wild Creatures\0";
            DRGui::ArrowSelector("Target", &settings.CurrentTargetSetting, TargetNames, ImVec2(ImGui::GetWindowWidth() / 2, 0.0f), false);

            ImGui::Spacing();
            ImGui::Separator();
            ImGui::Spacing();

            DRGui::CheckBox("##Auto", &settings.AutoFillTurrets);
            ImGui::EndDisabled();
            ImGui::SameLine();
            ImGui::PushItemWidth(ImGui::GetWindowWidth() - 27);
            DRGui::SliderInt("Auto Fill Ammo", &settings.MaxBulletsPerTurret, 1, 2400);
            ImGui::PopItemWidth();

        } ImGui::EndChild();
    }
    ImGui::PopStyleVar(2);
}
/* * * * * *  Build Header End   * * * * * */


#pragma mark - Settings Header -

/* * * * * * * * * * * * * * * * * * * * * * */
/* * * * * * Settings Header Begin * * * * * */
/* * * * * * * * * * * * * * * * * * * * * * */

void UserMenu::SettingsHeader()
{
    ImGui::PushFont(NULL, style.FontSizeBase * 1.5f);
    ImGui::Text("Color");
    ImGui::PopFont();

    ImGui::Columns(2, nullptr, false); {
        ImGui::Spacing();
        for (const auto& entry : C0L0R) {
            if (DRGui::ColorEdit4(entry.name, (float*)&style.Colors[entry.idx]))
            {
                bColorChanged = true; bSaveColor = true;
            }
            ImGui::NextColumn();
            ImGui::Spacing();
        }

        if (bColorChanged)
        {
            style.Colors[ImGuiCol_Separator]            = style.Colors[ImGuiCol_Border];
            style.Colors[ImGuiCol_SeparatorHovered]     = style.Colors[ImGuiCol_Border];
            style.Colors[ImGuiCol_SeparatorActive]      = style.Colors[ImGuiCol_Border];

            style.Colors[ImGuiCol_Button]               = style.Colors[ImGuiCol_FrameBg];
            style.Colors[ImGuiCol_ButtonHovered]        = style.Colors[ImGuiCol_FrameBgHovered];
            style.Colors[ImGuiCol_ButtonActive]         = style.Colors[ImGuiCol_FrameBgActive];

            style.Colors[ImGuiCol_FrameBgHovered]       = style.Colors[ImGuiCol_FrameBg];
            style.Colors[ImGuiCol_FrameBgActive]        = style.Colors[ImGuiCol_FrameBg];

            style.Colors[ImGuiCol_Header]               = style.Colors[ImGuiCol_FrameBg];
            style.Colors[ImGuiCol_HeaderHovered]        = style.Colors[ImGuiCol_FrameBgHovered];
            style.Colors[ImGuiCol_HeaderActive]         = style.Colors[ImGuiCol_FrameBgActive];

            style.Colors[ImGuiCol_ScrollbarGrab]        = style.Colors[ImGuiCol_SliderGrab];
            style.Colors[ImGuiCol_ScrollbarGrabHovered] = style.Colors[ImGuiCol_SliderGrab];
            style.Colors[ImGuiCol_ScrollbarGrabActive]  = style.Colors[ImGuiCol_SliderGrab];

            style.Colors[ImGuiCol_CheckMark]            = style.Colors[ImGuiCol_SliderGrabActive];

            bColorChanged = false;
        }
    } ImGui::Columns(1);

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();


    ImGui::Columns(2, nullptr, false);

    if (DRGui::Button("Reset Settings")) {settings.Reset();}

    ImGui::NextColumn();
    DRGui::CheckBox("Allow Menu Move", &settings.AllowWindowMove);

    ImGui::Columns(1);

    //ImGui::SameLine();
    //DRGui::CheckBox("Streamer Mode", &settings.StreamerMode);
}

/* * * * * * Settings Header End * * * * * */




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma mark - External Drawing -

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////// IMGUI EXTERNAL DRAWING ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void DrawCrosshair()
{
    ImDrawList* draw_list;

    if (settings.g_CrosshairSettings.make_foreground)
        draw_list = ImGui::GetForegroundDrawList();
    else
        draw_list = ImGui::GetBackgroundDrawList();

    ImVec2 center = ImVec2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);

    float size = settings.g_CrosshairSettings.size * SCREEN_SCALE;
    float thickness = settings.g_CrosshairSettings.thickness * SCREEN_SCALE;
    float gap = settings.g_CrosshairSettings.gap * SCREEN_SCALE;
    ImU32 color = settings.g_CrosshairSettings.color;

    bool outline_enabled = settings.g_CrosshairSettings.outline_cross;
    ImU32 outline_color = settings.g_CrosshairSettings.outline_color;
    float circle_radius = settings.g_CrosshairSettings.small_circle_radius * SCREEN_SCALE;

    float dot_radius = settings.g_CrosshairSettings.small_dot_radius * SCREEN_SCALE;

    auto draw_crosshair_line = [&](ImVec2 start, ImVec2 end, ImU32 col, float thick)
    {
        draw_list->AddLine(start, end, col, thick);
    };

    std::vector<std::pair<ImVec2, ImVec2>> lines;

    switch (settings.g_CrosshairSettings.type)
    {
        case CrosshairType::FourSticks:
            lines.emplace_back(ImVec2(center.x - gap - size, center.y), ImVec2(center.x - gap, center.y));
            lines.emplace_back(ImVec2(center.x + gap, center.y), ImVec2(center.x + gap + size, center.y));
            lines.emplace_back(ImVec2(center.x, center.y - gap - size), ImVec2(center.x, center.y - gap));
            lines.emplace_back(ImVec2(center.x, center.y + gap), ImVec2(center.x, center.y + gap + size));
            break;

        case CrosshairType::FourSticksRotated45:
            {
                float angle = IM_PI / 4.0f;

                ImVec2 offsets[] =
                {
                    ImVec2(cos(angle), sin(angle)),
                    ImVec2(cos(3 * angle), sin(3 * angle)),
                    ImVec2(cos(5 * angle), sin(5 * angle)),
                    ImVec2(cos(7 * angle), sin(7 * angle))
                };

                for (auto& dir : offsets)
                {
                    ImVec2 start = ImVec2(center.x + dir.x * (gap), center.y + dir.y * (gap));
                    ImVec2 end = ImVec2(center.x + dir.x * (gap + size), center.y + dir.y * (gap + size));
                    lines.emplace_back(start, end);
                }
            }
            break;

        case CrosshairType::ThreeSticks:
            lines.emplace_back(ImVec2(center.x - gap - size, center.y), ImVec2(center.x - gap, center.y));
            lines.emplace_back(ImVec2(center.x + gap, center.y), ImVec2(center.x + gap + size, center.y));
            lines.emplace_back(ImVec2(center.x, center.y - gap - size), ImVec2(center.x, center.y - gap));
            break;

        case CrosshairType::Triangle:
            {
                float angles[3] =
                {
                    -IM_PI / 2.0f,
                    5.0f * IM_PI / 6.0f,
                    IM_PI / 6.0f
                };

                for (int i = 0; i < 3; ++i)
                {
                    float angle = angles[i];
                    ImVec2 dir = ImVec2(cos(angle), sin(angle));
                    ImVec2 start = ImVec2(center.x + dir.x * gap, center.y + dir.y * gap);
                    ImVec2 end = ImVec2(center.x + dir.x * (gap + size), center.y + dir.y * (gap + size));
                    lines.emplace_back(start, end);
                }
            }
    }

    if (outline_enabled) {
        for (const auto& line : lines) {
            draw_crosshair_line(line.first, line.second, outline_color, 3.0f);
        }

        if (settings.g_CrosshairSettings.small_circle_enabled)
        {
            draw_list->AddCircle(
                center + ImVec2(0.5f, 0.5f),
                circle_radius,
                outline_color,
                24,
                3.0f
            );
        }
    }

    if (settings.g_CrosshairSettings.cross_enabled) {
        for (const auto& line : lines) {
            draw_crosshair_line(line.first, line.second, color, thickness);
        }
    }

    if (settings.g_CrosshairSettings.small_circle_enabled)
    {
        draw_list->AddCircle(
            center + ImVec2(0.5f, 0.5f),
            circle_radius,
            color,
            24,
            thickness
        );
    }

    if (settings.g_CrosshairSettings.small_dot_enabled)
    {
        draw_list->AddCircleFilled(
            center + ImVec2(0.5f, 0.5f),
            dot_radius,
            color
        );
    }
}




#pragma mark - JSON Parse -

#include "Utilities/rapidjson/document.h"

template <typename EnumType>
EnumType ParseEnumOrDefault(const std::string& str, EnumType defaultValue) {
    auto enumOpt = magic_enum::enum_cast<EnumType>(str);
    return enumOpt.value_or(defaultValue);
}

std::string UserMenu::FetchDataFromURL(const std::string& url) {
    __block NSData *responseData = nil;
    __block NSError *responseError = nil;
    dispatch_semaphore_t sema = dispatch_semaphore_create(0);

    NSString *nsurl = [NSString stringWithUTF8String:url.c_str()];
    NSURL *URL = [NSURL URLWithString:nsurl];
    if (!URL)
        return "";

    NSURLSession *session = [NSURLSession sharedSession];
    NSURLSessionDataTask *dataTask = [session dataTaskWithURL:URL
                                            completionHandler:^(NSData *data, NSURLResponse *response, NSError *error) {
        responseData = data;
        responseError = error;
        dispatch_semaphore_signal(sema);
    }];
    [dataTask resume];
    dispatch_semaphore_wait(sema, DISPATCH_TIME_FOREVER);

    if (responseError)
        return "";

    if (!responseData)
        return "";

    std::string result((const char *)[responseData bytes], [responseData length]);

    return result;
}

void UserMenu::ParseJSONData(char* jsonData, std::vector<SessionInfo>& sessions) {

    using namespace rapidjson;

    Document document;
    document.ParseInsitu(jsonData);

    if (document.HasParseError() || !document.IsArray()) return;

    sessions.reserve(document.Size());

    for (auto& session : document.GetArray()) {
        SessionInfo info;

        info.name = session["Name"].GetString();
        info.nameLower = ToLower(info.name);
        info.numPlayers = session["NumPlayers"].GetInt();
        info.maxPlayers = session["MaxPlayers"].GetInt();
        info.ipPort = fmt::format("{}:{}", session["IP"].GetString(), session["Port"].GetInt());

        const char* clusterStr = session["ClusterId"].GetString();

        std::string clusterBuffer(clusterStr);
        Document clusterDoc;
        clusterDoc.ParseInsitu(&clusterBuffer[0]);

        if (!clusterDoc.HasParseError()) {
            info.mode = ParseEnumOrDefault<ModeType>(clusterDoc["Mode"].GetString(), ModeType::Mode);
            info.region = ParseEnumOrDefault<RegionType>(clusterDoc["REGION"].GetString(), RegionType::Region);
            info.difficulty = ParseEnumOrDefault<DifficultyType>(clusterDoc["Difficulty"].GetString(), DifficultyType::Difficulty);

            info.hasPassword = clusterDoc["HasPassword"].GetBool();
        }

        sessions.push_back(std::move(info));
    }

    auto partitionIt = std::partition(sessions.begin(), sessions.end(),
        [](const SessionInfo& s)
        {
            return s.numPlayers != 0;
        }
    );

    std::sort(sessions.begin(), partitionIt,
        [](const SessionInfo& a, const SessionInfo& b)
        {
            return a.numPlayers > b.numPlayers;
        }
    );
}





#pragma mark - Server List -

/* * * * * * * * * * * * * * * * * * * * */
/* * * * * * Server List Begin * * * * * */
/* * * * * * * * * * * * * * * * * * * * */

std::vector<SessionInfo> sessions;

template <typename EnumType>
ImColor GetColorForEnum(EnumType enumValue) {
    if constexpr (std::is_same_v<EnumType, RegionType>) {
        switch (enumValue) {
            case RegionType::EU: return blue;
            case RegionType::NA: return yellow;
            case RegionType::Asia: return red;
            case RegionType::ANZ: return green;
            default: return white;
        }
    } else if constexpr (std::is_same_v<EnumType, DifficultyType>) {
        switch (enumValue) {
            case DifficultyType::Easy: return green;
            case DifficultyType::Medium: return blue;
            case DifficultyType::Hard: return red;
            case DifficultyType::Brutal: return purple;
            default: return white;
        }
    } else if constexpr (std::is_same_v<EnumType, ModeType>) {
        switch (enumValue) {
            case ModeType::PVE: return green;
            case ModeType::PVX: return orange;
            case ModeType::PVP: return red;
            default: return white;
        }
    } else {
        return white;
    }
}

struct RecentServerInfo : SessionInfo
{
    using SessionInfo::SessionInfo;

    std::wstring Password;

    RecentServerInfo(const SessionInfo& Session, std::wstring const& _Password) : SessionInfo(Session), Password(_Password) {}
};

std::vector<RecentServerInfo> RecentServers;

void OnServerJoined(const SessionInfo& Session, std::wstring const& Password = L"")
{
    RecentServers.emplace_back(Session, Password);
}

void UserMenu::ServerList()
{
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(1.0f, 4.0f));
    ImGui::Columns(3, "srv", false);

    if (DRGui::Button("Join Server", ImVec2(-0.1f, 0)) && selectedSession)
    {
        if (!sessions.empty() && !selectedSession->ipPort.empty())
        {
            std::wstring IP(selectedSession->ipPort.begin(), selectedSession->ipPort.end());

            if (selectedSession->hasPassword)
            {
                auto JoinServerWithPassword = [&](const std::string& Password) -> void
                {
                    if (UEngine::GetEngine() && UWorld::GetWorld())
                    {
                        std::wstring Pass(Password.begin(), Password.end());
                        if (UShooterLocalPlayer* LP = UObject::Cast<UShooterLocalPlayer>(GetLocalPlayer()); LP && !Pass.empty())
                            LP->SetServerLoginPassword(Pass.c_str(), IP.c_str(), static_cast<AShooterPlayerController_Menu*>(LP->PlayerController));

                        SetClientTravel_Internal(UEngine::GetEngine(), UWorld::GetWorld(), IP.c_str(), ETravelType::TRAVEL_Absolute);

                        OnServerJoined(*selectedSession, Pass);
                    }
                };

                std::shared_ptr<std::string> OutStr = std::make_shared<std::string>();
                iOS::ShowTextInputAlert(@"", @"Enter Password", *OutStr, [&](bool Success)
                {
                    if (!Success)
                        return;

                    JoinServerWithPassword(*OutStr);
                });
            }
            else
            {

                if (UEngine::GetEngine() && UWorld::GetWorld())
                {
                    SetClientTravel_Internal(UEngine::GetEngine(), UWorld::GetWorld(), IP.c_str(), ETravelType::TRAVEL_Absolute);
                    OnServerJoined(*selectedSession, L"");
                }



            }
        }
    }
    ImGui::NextColumn();
 // ???????????????????????????????????????????????????????????? // ???????????????????????????????????????????????????????????? // ????????????????????????????????????????????????????????????
    // if (!serverPassword.empty()) { // ????????????????????????????????????????????????????????????
    //     if (selectedSession && !selectedSession->ipPort.empty()) {
    //         std::wstring IP(selectedSession->ipPort.begin(), selectedSession->ipPort.end());

    //         if (UShooterLocalPlayer* LP = GetLocalPlayer(); LP && LP->PlayerController) {
    //             LP->SetServerLoginPassword(FString(serverPassword.c_str()), IP.c_str(), static_cast<AShooterPlayerController_Menu*>(LP->PlayerController));

    //             CallClientTravel(IP.c_str());

    //             //PassJoin = false;
    //         }
    //     }
    // }
 // ???????????????????????????????????????????????????????????? // ???????????????????????????????????????????????????????????? // ???????????????????????????????????????????????????????????? // ????????????????????????????????????????????????????????????

    if (DRGui::Button("Get Server List", ImVec2(-0.1f, 0)) && !bIsDispatchActive) {
        selectedSession = nullptr;
        sessions.clear();
        // TODO: Supply your own authenticated server-directory implementation.
    } ImGui::NextColumn();


    if (DRGui::Button("Recent Server", ImVec2(-0.1f, 0)))
    {

    } ImGui::Columns(1);

    float totalWidth = ImGui::GetContentRegionAvail().x;

    ImGui::Columns(5, nullptr, false);

    ImGui::SetColumnWidth(0, totalWidth * (2.0f / 6.0f));

    float col_width = totalWidth * (1.0f / 6.0f) + 5.f;

    ImGui::SetColumnWidth(1, col_width);
    ImGui::SetColumnWidth(2, col_width);
    ImGui::SetColumnWidth(3, col_width);
    ImGui::SetColumnWidth(4, col_width);

    DRGui::InputTextStr("##SrvSrch", ICON_FA_SEARCH "  Search", &searchSrvBuffer, -0.1f, ImGuiInputTextFlags_ReadOnly);

    if (ImGui::IsItemClicked() && !alertControllerFlag) {
        alertControllerFlag = true;

        ShowTextInputAlert<std::string>(
            @"Search",
            nil,
            @"",
            @"",
            true,

            [&](const std::string& enteredText) {
                searchSrvBuffer = enteredText.c_str();
                searchSrvBuffer.shrink_to_fit();
                searchSrvBuffer.reserve(128);

                searchSrvStrLower = ToLower(searchSrvBuffer);

                alertControllerFlag = false;
                currentPage = 0;
            },

            [&](const std::string& /*unused*/) {
                alertControllerFlag = false;
            }
        );
    } ImGui::NextColumn();

    if (DRGui::Button(sortByPassword ? ICON_FA_LOCK : ICON_FA_LOCK_OPEN, ImVec2(-0.1f, 0))) {
        sortByPassword = !sortByPassword;
        currentPage = 0;
    } ImGui::NextColumn();

    auto FilterButton = [&](auto& CurrentFilter) -> void {

        if (DRGui::Button(
            magic_enum::enum_name(CurrentFilter).data(), ImVec2(-0.1f, 0))
        )
        {
            auto enumValues = magic_enum::enum_values<std::decay_t<decltype(CurrentFilter)>>();
            size_t CurrentIdx = magic_enum::enum_index(CurrentFilter).value_or(0);

            CurrentIdx = (CurrentIdx + 1) % magic_enum::enum_count<std::decay_t<decltype(CurrentFilter)>>();
            CurrentFilter = enumValues[CurrentIdx];

            currentPage = 0;
        } ImGui::NextColumn();
    };

    FilterButton(RegionFilter);
    FilterButton(DifficultyFilter);
    FilterButton(ModeFilter);

    ImGui::Columns(1);
    ImGui::PopStyleVar();

    if (!bIsDispatchActive && !sessions.empty()) {

        uint16_t start = currentPage * pageSize;
        uint16_t end = start + pageSize;

        totalFiltered = 0;
        uint16_t displayed = 0;


        ImGui::PushFont(NULL, style.FontSizeBase * 0.8f);

        float playersColWidth = ImGui::CalcTextSize("50/50").x;
        float settingsColWidth = ImGui::CalcTextSize("Asia/Medium/PVP").x;
        float ipAddressColWidth = ImGui::CalcTextSize("address:port").x;

        ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0, 0, 0, 0));
        if (ImGui::BeginTable("SrvTbl", 4, tableFlags, ImVec2(-FLT_MIN, ImGui::GetContentRegionAvail().y - 50))) {
            ImGui::TableSetupScrollFreeze(0, 1);
            ImGui::TableSetupColumn(ICON_FA_PAGER " Servers", ImGuiTableColumnFlags_WidthStretch, 0.0f);
            ImGui::TableSetupColumn(ICON_FA_USER_GROUP, ImGuiTableColumnFlags_WidthFixed, playersColWidth);
            ImGui::TableSetupColumn(ICON_FA_GEARS " Settings", ImGuiTableColumnFlags_WidthFixed, settingsColWidth);
            ImGui::TableSetupColumn(ICON_FA_WIFI " IP Address", ImGuiTableColumnFlags_WidthFixed, ipAddressColWidth);
            ImGui::TableHeadersRow();


            for (size_t i = 0; i < sessions.size(); ++i) {

                SessionInfo& serverEntry = sessions[i];

                if (sortByPassword && !serverEntry.hasPassword) continue;
                if (!sortByPassword && serverEntry.hasPassword) continue;

                if (RegionFilter != RegionType::Region && serverEntry.region != RegionFilter)
                    continue;

                if (DifficultyFilter != DifficultyType::Difficulty && serverEntry.difficulty != DifficultyFilter)
                    continue;

                if (ModeFilter != ModeType::Mode && serverEntry.mode != ModeFilter)
                    continue;

                if (!searchSrvStrLower.empty() && serverEntry.nameLower.find(searchSrvStrLower) == std::string::npos)
                    continue;

                totalFiltered++;

                if (totalFiltered > end)
                    continue;

                if (totalFiltered > start && displayed < pageSize) {
                    ImGui::TableNextRow();

                    ImGui::TableSetColumnIndex(0);
                    bool isSelected = (selectedSession == &serverEntry);

                    ImGui::PushID(i);
                    if (ImGui::Selectable(serverEntry.name.c_str(), isSelected, ImGuiSelectableFlags_SpanAllColumns)) {
                        selectedSession = &serverEntry;
                    }

                    ImGui::PopID();
                    ImGui::TableSetColumnIndex(1);
                    ImGui::Text("%d/%d", serverEntry.numPlayers, serverEntry.maxPlayers);

                    ImGui::TableSetColumnIndex(2);
                    ImGui::TextColored(GetColorForEnum(serverEntry.region), "%s", magic_enum::enum_name(serverEntry.region).data());
                    ImGui::SameLine(0, 0);
                    ImGui::Text("/");
                    ImGui::SameLine(0, 0);
                    ImGui::TextColored(GetColorForEnum(serverEntry.difficulty), "%s", magic_enum::enum_name(serverEntry.difficulty).data());
                    ImGui::SameLine(0, 0);
                    ImGui::Text("/");
                    ImGui::SameLine(0, 0);
                    ImGui::TextColored(GetColorForEnum(serverEntry.mode), "%s", magic_enum::enum_name(serverEntry.mode).data());

                    ImGui::TableSetColumnIndex(3);
                    ImGui::TextDisabled("%s", serverEntry.ipPort.c_str());

                    if (isSelected) {
                        ImGui::SetItemDefaultFocus();
                    }

                    displayed++;
                }
            } ImGui::EndTable();
        } ImGui::PopStyleColor();
        ImGui::PopFont();

        uint16_t totalPages = (totalFiltered + pageSize - 1) / pageSize;

        if (currentPage >= totalPages && totalPages > 0) {
            currentPage = totalPages - 1;
        }

        ImGui::Columns(3, "tfsfer", false);

        if (currentPage > 0) {
            if (DRGui::Button(ICON_FA_CARET_LEFT, ImVec2(-FLT_MIN, 0))) {
                currentPage--;
            }
        } else {
            ImGui::BeginDisabled();
            DRGui::Button(ICON_FA_CARET_LEFT, ImVec2(-FLT_MIN, 0));
            ImGui::EndDisabled();
        }
        ImGui::NextColumn();

        std::string pageIndicator = fmt::format("Page {} of {}", totalFiltered == 0 ? 0 : currentPage + 1, totalPages);
        ImGui::Text("%s", pageIndicator.c_str());
        ImGui::NextColumn();

        if (currentPage < totalPages - 1) {
            if (DRGui::Button(ICON_FA_CARET_RIGHT, ImVec2(-FLT_MIN, 0))) {
                currentPage++;
            }
        } else {
            ImGui::BeginDisabled();
            DRGui::Button(ICON_FA_CARET_RIGHT, ImVec2(-FLT_MIN, 0));
            ImGui::EndDisabled();
        }

        ImGui::Columns(1);
    }
}
/* * * * * * Server List End * * * * * */

#pragma mark - Player List -

/* * * * * * * * * * * * * * * * * * * * */
/* * * * * * Player List Begin * * * * * */
/* * * * * * * * * * * * * * * * * * * * */

bool bPlayerList = false;

std::vector<PlayerDisplayInfo> playerListDisplay;

void ShooterPlayerStatePE_Hook(AShooterPlayerState* Object, UFunction* Function, void* Parms);
VMTHookManager ShooterPlayerStatePE(&ShooterPlayerStatePE_Hook, Offsets::ProcessEventIdx);

void UserMenu::PlayerList()
{
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(1.0f, 4.0f));
    ImGui::Columns(2, nullptr, false);

    if (DRGui::Button("Get Online Players", ImVec2(-0.1f, 0)))
    {
        ShooterPlayerControllerQueue.Add([&](AShooterPlayerController* PC)
        {
            if (AShooterPlayerState* PlayerState = UObject::Cast<AShooterPlayerState>(PC->PlayerState))
            {
                ShooterPlayerStatePE.Swap(PlayerState);

                bPlayerList = false;

                PlayerState->ServerGetAlivePlayerConnectedData();
            }
        });

    } ImGui::NextColumn();

    if (DRGui::Button("Copy ID", ImVec2(-0.1f, 0)) && g_SelectedPlayerID) {
        NSString *nsPlayerIdStr = [NSString stringWithFormat:@"%llu", g_SelectedPlayerID];
        if (nsPlayerIdStr)
            [UIPasteboard generalPasteboard].string = nsPlayerIdStr;
    }

    ImGui::Columns(1);

    ImGui::Columns(4, "plr", false);

    auto PlayerCommand = [&](const char* label, const wchar_t* commandFormat) {
        if (DRGui::Button(label, ImVec2(-0.1f, 0)) && g_SelectedPlayerID) { // && GetPlayerController()) {
           auto args = fmt::make_wformat_args(g_SelectedPlayerID);
           std::wstring command = fmt::vformat(fmt::wstring_view(commandFormat), args);
           GetPlayerController()->ServerCheat(command.c_str());
        }
        ImGui::NextColumn();
    };

    PlayerCommand("TP", L"cheat TeleportToPlayer {}");
    PlayerCommand("Ban", L"cheat BanPlayer {}");
    PlayerCommand("Kill Player", L"cheat KillPlayer {}");
    PlayerCommand("Clear Inv", L"cheat ClearPlayerInventory {} 1 1 1");

    ImGui::Columns(1);

    DRGui::InputTextStr("##PlrSrch", ICON_FA_SEARCH "  Search", &searchPlrBuffer, -0.1f, ImGuiInputTextFlags_ReadOnly);

    if (ImGui::IsItemClicked() && !alertControllerFlag) {
        alertControllerFlag = true;

        ShowTextInputAlert<std::string>(
            @"Search",
            nil,
            @"",
            @"",
            true,

            [&](const std::string& enteredText) {
                searchPlrBuffer = enteredText.c_str();
                searchPlrBuffer.shrink_to_fit();
                searchPlrBuffer.reserve(128);

                searchPlrStrLower = ToLower(searchPlrBuffer);

                alertControllerFlag = false;
            },

            [&](const std::string& /*unused*/) {
                alertControllerFlag = false;
            }
        );
    }

    ImGui::PopStyleVar();

    if (bPlayerList && !playerListDisplay.empty())
    {
        ImGui::PushFont(NULL, style.FontSizeBase * 0.8f);
        ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0, 0, 0, 0));
        if (ImGui::BeginTable("PlrTbl", 3, tableFlags, ImVec2(-FLT_MIN, ImGui::GetContentRegionAvail().y - 20))) {
            ImGui::TableSetupScrollFreeze(0, 1);
            ImGui::TableSetupColumn(ICON_FA_USER_TAG " Name", ImGuiTableColumnFlags_WidthFixed);
            ImGui::TableSetupColumn(ICON_FA_ID_CARD " ID", ImGuiTableColumnFlags_WidthFixed);
            ImGui::TableSetupColumn(ICON_FA_USERS " Tribe Name", ImGuiTableColumnFlags_WidthFixed);
            ImGui::TableHeadersRow();

            for(size_t i = 0; i < playerListDisplay.size(); ++i)
            {
                const PlayerDisplayInfo& playerEntry = playerListDisplay[i];

                if (!searchPlrStrLower.empty() && playerEntry.PlayerNameLower.find(searchPlrStrLower) == std::string::npos)
                    continue;

                ImGui::TableNextRow();

                ImGui::TableSetColumnIndex(0);
                bool isSelected = (g_SelectedPlayerID == playerEntry.PlayerId);

                ImGui::PushID(i);
                if (ImGui::Selectable(playerEntry.PlayerName.c_str(), isSelected, ImGuiSelectableFlags_SpanAllColumns)) {
                    g_SelectedPlayerID = playerEntry.PlayerId;
                }

                ImGui::PopID();
                ImGui::TableSetColumnIndex(1);
                ImGui::Text("%llu", playerEntry.PlayerId);

                ImGui::TableSetColumnIndex(2);
                ImGui::Text("%s", playerEntry.PlayerTribeName.c_str());

                if (isSelected) {
                    ImGui::SetItemDefaultFocus();
                }
            } ImGui::EndTable();
        }
        ImGui::PopStyleColor();
        ImGui::PopFont();
    }
}
/* * * * * * Player List End * * * * * */

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string ToLower(const std::string& str) {
    std::string result(str.size(), '\0');

    std::transform(str.begin(), str.end(), result.begin(),
                   [](unsigned char c) -> char {
                       return static_cast<char>(std::tolower(c));
                   });

    return result;
}

#include "../Utilities/DeepCopy.hpp"


/* * Players Online Data * */
void ShooterPlayerStatePE_Hook(AShooterPlayerState* Object, UFunction* Function, void* Parms)
{

    static const FName NAME_ClientGetAlivePlayerConnectedData = FName(TEXT("ClientGetAlivePlayerConnectedData"));
    if (Function->Name == NAME_ClientGetAlivePlayerConnectedData)
    {

        auto* param = (Params::ShooterPlayerState_ClientGetAlivePlayerConnectedData*)Parms;

        FieldSpec<FString> PlayerNameField
        {
            offsetof(FAlivePlayerDataInfo, PlayerName)
        };

        PlayerNameField.addDestination<std::string>(offsetof(PlayerDisplayInfo, PlayerName),
            [](const FString& name) -> std::string
            {
                return name.ToString();
            }
        );

        PlayerNameField.addDestination<std::string>(offsetof(PlayerDisplayInfo, PlayerNameLower),
            [](const FString& name) -> std::string
            {
                return ToLower(name.ToString());
            }
        );

        FieldSpec<FString> TribeNameField
        {
            offsetof(FAlivePlayerDataInfo, TribeName)
        };

        TribeNameField.addDestination<std::string>(offsetof(PlayerDisplayInfo, PlayerTribeName),
            [](const FString& name) -> std::string
            {
                return name.ToString();
            }
        );

        FieldSpec<int64_t> PlayerIdField
        {
            offsetof(FAlivePlayerDataInfo, PlayerId)
        };

        PlayerIdField.addDestination<int64_t>(offsetof(PlayerDisplayInfo, PlayerId));

        FieldSpec<int64_t> TargetingTeamIDField
        {
            offsetof(FAlivePlayerDataInfo, TargetingTeamID)
        };

        TargetingTeamIDField.addDestination<int64_t>(offsetof(PlayerDisplayInfo, TribeId));

        if (param->List)
        {
            DeepCopyArray(param->List, playerListDisplay, PlayerNameField,
                                        TribeNameField, PlayerIdField, TargetingTeamIDField);

            bPlayerList = true;
        }

        return ShooterPlayerStatePE.Reset(Object);
    }

    return ShooterPlayerStatePE.InvokeOriginal(Object, Function, Parms);
}


#pragma mark - Admin Header -

/* * * * * * * * * * * * * * * * * * * * * * */
/* * * * * * * Admin Header Begin  * * * * * */
/* * * * * * * * * * * * * * * * * * * * * * */

#include "AdminMaps.hpp"

static inline void SendCheat(std::wstring cmd, bool bIsAdminCheat = false)
{
    // ShooterPlayerControllerQueue.Add([&](AShooterPlayerController* PC)
    ShooterPlayerControllerQueue.Add([cmd = std::move(cmd), bIsAdminCheat](AShooterPlayerController* PC)
    {
        // if (PC->bIsServerAdmin)
        // {
                if (!bIsAdminCheat) PC->ServerCheat(cmd.c_str());
                else                PC->AdminCheat(cmd.c_str());
        // }
    });
}

static inline void SendCheat(const wchar_t* cmd, bool bIsAdminCheat = false) {
    SendCheat(std::wstring(cmd), bIsAdminCheat);
}

template<typename... Args>
static inline void SendCheatFmt(const wchar_t* fmtstr, Args&&... args) {
    SendCheat(fmt::format(fmt::runtime(fmtstr), std::forward<Args>(args)...));
}


#include "../Utilities/ConvertUtils.hpp"

inline std::wstring wtrim(std::wstring s)
{
    while (!s.empty() && std::iswspace(s.front())) s.erase(s.begin());
    while (!s.empty() && std::iswspace(s.back()))  s.pop_back();
    return s;
}

inline bool parseIntW(const std::wstring& s, int& out)
{
    try { size_t p=0; int v=std::stoi(s, &p, 10); if(p!=s.size()) return false; out=v; return true; }
    catch (...) { return false; }
}
inline bool parseDoubleW(const std::wstring& s, double& out)
{
    try { size_t p=0; double v=std::stod(s, &p); if(p!=s.size()) return false; out=v; return true; }
    catch (...) { return false; }
}

static inline void ShowInvalidAlert(NSString* title = @"Invalid value",
                                    NSString* msg   = @"Please enter a valid number.")
{
   iOS::ShowAlert(title, msg, @"OK", nullptr, nullptr);
}

static void PromptInt(NSString* uiTitle,
                                  NSString* placeholder,
                                  const wchar_t* cheatName,
                                  std::optional<std::pair<int,int>> bounds = std::nullopt)
{
    auto inputBuf = std::make_shared<std::wstring>();
    iOS::ShowTextInputAlert(
        uiTitle,
        nil,
        *inputBuf,
        [inputBuf, cheatName, bounds](bool ok)
        {
            if (!ok) return;

            std::wstring s = wtrim(*inputBuf);
            int value = 0;
            if (!parseIntW(s, value)) { ShowInvalidAlert(); return; }

            if (bounds) {
                auto [lo, hi] = *bounds;
                if (value < lo || value > hi) {
                    iOS::ShowAlert(@"Out of range",
                                   [NSString stringWithFormat:@"Enter a value between %d and %d.", lo, hi],
                                   @"OK", nil, nil);
                    return;
                }
            }

            std::wstring cmd = fmt::format(L"cheat {} {}", cheatName, value);
            SendCheat(cmd);
        }
    );
}

void UserMenu::AdminHeader() {
    ExecutionTimer::Synchronize(206, true);

    switch (menuState.subPages[MenuPage::Admin]) {
        case SubPage::Items:
        {


            static const char* currentItemName = itemsMap.begin()->first;

            ImGui::Columns(2, nullptr, false);
            DRGui::SliderInt("Amount", &ItemValue, 1, 500);
            ImGui::NextColumn();
            DRGui::SliderInt("Stacks", &StackValue, 1, 100);
            ImGui::Columns(1);

            if (DRGui::Button("Spawn Item", ImVec2(-0.1f, 0))) {
                const wchar_t* currentValue = itemsMap[currentItemName];

                std::wstring command = fmt::format(L"admincheat giveslotitem \"{}\" 1 {}", currentValue, ItemValue);

                for (int i = 1; i < StackValue; i++) {
                    command += fmt::format(L" | admincheat giveslotitem \"{}\" 1 {}", currentValue, ItemValue);
                }

                SendCheat(command);
            }


            DRGui::InputTextStr("##Aaaa", ICON_FA_SEARCH "  Search Item", &searchBufferItem, -0.1f, ImGuiInputTextFlags_ReadOnly);

            if (ImGui::IsItemClicked() && !alertControllerFlag) {
                alertControllerFlag = true;

                ShowTextInputAlert<std::string>(
                                                @"Search",
                                                nullptr,
                                                @"",
                                                @"",
                                                true,

                                                [&](const std::string& enteredText) {
                                                    searchBufferItem = enteredText.c_str();
                                                    searchBufferItem.shrink_to_fit();
                                                    searchBufferItem.reserve(128);
                                                    searchBufferItemLower = ToLower(searchBufferItem);
                                                    alertControllerFlag = false;
                                                },

                                                [&](const std::string& ) {
                                                    alertControllerFlag = false;
                                                }
                                                );
            }

            ImGui::PushItemWidth(-FLT_MIN);
            if (ImGui::BeginListBox("##Items", ImVec2(0, 185))) {
                int itemNum = 0;
                for (auto& item : itemsMap) {
                    std::string itemNameLower = ToLower(item.first);
                    if (itemNameLower.find(searchBufferItemLower) != std::string::npos) {
                        const bool isSelected = (selectedItem == itemNum);
                        if (ImGui::Selectable(item.first, isSelected)) {
                            currentItemName = item.first;
                            selectedItem = itemNum;
                        }
                        if (isSelected) {
                            ImGui::SetItemDefaultFocus();
                        }
                    }
                    ++itemNum;
                }
                ImGui::EndListBox();
            }
            ImGui::PopItemWidth();

        }
            break;

        case SubPage::Dino:
        {

            dinoSpawnsAllOther.insert(specialDinoSpawnsAllOther.begin(), specialDinoSpawnsAllOther.end());
            static const char* currentDisplayNameDino = dinoSpawnsAllOther.begin()->first;

            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(1.0f, 4.0f));

            ImGui::Columns(3, "dino_1", false);


            if (DRGui::Button("Imprint", ImVec2(-0.1f, 0))) {
                PromptInt(@"Imprint", @"Number", L"SetImprintQuality");
            }
            ImGui::NextColumn();
            if (DRGui::Button("Set Age", ImVec2(-0.1f, 0))) {
                PromptInt(@"Set Age", @"1 to 20", L"SetBabyAge", std::make_pair(1, 20));
            }
            ImGui::NextColumn();

            if (DRGui::Button("Size Dino", ImVec2(-0.1f, 0))) {
                PromptInt(@"Set Size", @"12345", L"ChangeSize");
            }

            ImGui::Columns(2, "dino_2", false);

            if (DRGui::Button("Force Tame", ImVec2(-0.1f, 0))) {
                SendCheat(L"cheat ForceTame");
            } ImGui::NextColumn();

            if (DRGui::Button("Force Mate", ImVec2(-0.1f, 0))) {
                SendCheat(L"cheat ForceMate");
            } ImGui::NextColumn();

            ImGui::Columns(1);
            ImGui::PopStyleVar();
            ImGui::Separator();

            DRGui::CheckBox("Tamed", &isTamed);
            ImGui::SameLine();
            DRGui::SliderInt("Level", &DinoValue, 1, 500);

            if (DRGui::Button("Spawn Dino", ImVec2(-0.1f, 0))) {
                const wchar_t* currentValueDino = (dinoSpawnsAllOther)[currentDisplayNameDino];
                bool isSpecial = specialDinoSpawnsAllOther.find(currentDisplayNameDino) != specialDinoSpawnsAllOther.end();

                std::wstring commandDino;

                if (isSpecial) {
                    commandDino = isTamed ? fmt::format(L"cheat SpawnActorTamed \"{}\" {} 0 0", currentValueDino, DinoValue) : fmt::format(L"cheat SpawnActor \"{}\" {} 0 0", currentValueDino, DinoValue);
                } else {
                    commandDino = isTamed ? fmt::format(L"cheat GMSummon \"{}\" {}", currentValueDino, DinoValue) : commandDino = fmt::format(L"cheat Summon \"{}\"", currentValueDino);
                }

                SendCheat(commandDino);
            }

            DRGui::InputTextStr("##Dddd", ICON_FA_SEARCH "  Search Dino", &searchBufferDino, -0.1f, ImGuiInputTextFlags_ReadOnly);

            if (ImGui::IsItemClicked() && !alertControllerFlag) {
                alertControllerFlag = true;

                ShowTextInputAlert<std::string>(
                                                @"Search",
                                                nullptr,
                                                @"",
                                                @"",
                                                true,

                                                [&](const std::string& enteredText) {
                                                    searchBufferDino = enteredText.c_str();
                                                    searchBufferDino.shrink_to_fit();
                                                    searchBufferDino.reserve(128);
                                                    searchBufferDinoLower = ToLower(searchBufferDino);
                                                    alertControllerFlag = false;
                                                },

                                                [&](const std::string& ) {
                                                    alertControllerFlag = false;
                                                }
                                                );
            }


            ImGui::PushItemWidth(-FLT_MIN);
            if (ImGui::BeginListBox("##Dinos", ImVec2(0, 120))) {
                int index = 0;
                for (auto& item : dinoSpawnsAllOther) {
                    std::string itemNameLower = ToLower(item.first);
                    if (itemNameLower.find(searchBufferDinoLower) != std::string::npos) {
                        bool isSelected = (currentDinoIndex == index);
                        if (ImGui::Selectable(item.first, isSelected)) {
                            currentDisplayNameDino = item.first;
                            currentDinoIndex = index;
                        }
                        if (isSelected)
                            ImGui::SetItemDefaultFocus();
                    }
                    ++index;
                }
                ImGui::EndListBox();
            }

            ImGui::PopItemWidth();

        }
            break;

        case SubPage::Dino_Color:
        {
            static const char kRegionItems[] = "Back\0Leg\0Abdomen\0";
            static constexpr std::array<int, 3> kRegionCodes = {0, 1, 2};

            ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, ImVec2(1.0f, 1.0f));

            DRGui::ArrowSelector("Region", &regionIdx, kRegionItems, ImVec2(350.0f, 0.0f), false);

            struct ColorBtn { const char* id; int code; const ImVec3* col; };

            static const std::array<ColorBtn, 18> kColorButtons = {{
                {"##1",  1,  &redColor},
                {"##2",  2,  &blueColor},
                {"##3",  3,  &greenColor},
                {"##4",  4,  &yellowColor},
                {"##5",  5,  &cyanColor},
                {"##6",  6,  &magentaColor},
                {"##7",  7,  &lightGreenColor},
                {"##8",  8,  &lightGreyColor},
                {"##9",  9,  &lightBrownColor},
                {"##10", 10, &lightOrangeColor},
                {"##11", 11, &lightYellowColor},
                {"##12", 12, &lightRedColor},
                {"##13", 13, &darkGreyColor},
                {"##14", 14, &blackColor},
                {"##15", 15, &brownColor},
                {"##16", 16, &darkGreenColor},
                {"##17", 17, &darkRedColor},
                {"##18", 18, &whiteColor},
            }};

            if (ImGui::BeginTable("ColorGrid", 2, ImGuiTableFlags_SizingStretchProp)) {
                for (size_t i = 0; i < kColorButtons.size(); ++i) {
                    if (i % 2 == 0) ImGui::TableNextRow();
                    ImGui::TableNextColumn();

                    ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(*kColorButtons[i].col, 0.90f));
                    ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, ImVec4(*kColorButtons[i].col, 0.45f));
                    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(*kColorButtons[i].col, 1.00f));
                    if (DRGui::Button(kColorButtons[i].id, ImVec2(170, 0))) {
                        const int regionCode = kRegionCodes[static_cast<size_t>(regionIdx)];
                        SendCheatFmt(L"admincheat SetTargetDinoColor \"{}\" {}", regionCode, kColorButtons[i].code);
                    }
                    ImGui::PopStyleColor(3);
                }
                ImGui::EndTable();
            }
            ImGui::PopStyleVar();

        }
            break;

        case SubPage::Commands:
        {

                if (DRGui::Button("Command Line", ImVec2(-0.1f, 0))) {
                                    auto inputBuf = std::make_shared<std::wstring>();

                                                        iOS::ShowTextInputAlert(
                                                            @"Command Line",
                                                            nil,
                                                            *inputBuf,
                                                            [inputBuf](bool ok) {
                                                                if (!ok) return;

                                                                const std::wstring& cmd = *inputBuf;
                                                                if (cmd.empty()) {
                                                                    iOS::ShowAlert(@"Empty Command",
                                                                                   @"Please type a command.",
                                                                                   @"OK", nullptr, nullptr);
                                                                    return;
                                                                }

                                                                // if (cmd.rfind("cheat ", 0) != 0)
                                                                //     return iOS::ShowAlert(@"Missing 'cheat'",
                                                                //                           @"Command should start with 'cheat '.",
                                                                //                           @"OK", nullptr, nullptr);

                                                                SendCheat(cmd);
                                                            }
                                                        );
                }

                ImGui::Columns(2, nullptr, false);

                if (DRGui::Button("Give All Skins", ImVec2(-0.1f, 0))) {
                    SendCheat(kGiveAllSkinsCmd);
                }ImGui::NextColumn();

                if (DRGui::Button("Spawn Amber", ImVec2(-0.1f, 0))) {
                    auto amberBuf = std::make_shared<std::wstring>();
                    iOS::ShowTextInputAlert(
                        @"AMBER",
                        nil,
                        *amberBuf,
                        [amberBuf](bool ok) {
                            if (!ok) return;

                            int amount = 0;
                            if (!parseIntW(wtrim(*amberBuf), amount)) { ShowInvalidAlert(); return; }

                            static constexpr const wchar_t* kAmberBP =
                                L"Blueprint'/Game/PrimalEarth/CoreBlueprints/Resources/PrimalItemResource_DinoAmber.PrimalItemResource_DinoAmber_C'";

                            std::wstring_view bpView{kAmberBP};
                            std::wstring cmd = fmt::format(
                                L"Admincheat GiveSlotItem \"{}\" 1 {}",
                                bpView, amount
                            );
                            SendCheat(cmd);
                        }
                    );
                }

                ImGui::Columns(1);

                DRGui::SliderInt("Amber Note", &AmberpickupVaule, 1, 500);
                ImGui::SameLine();

                if (DRGui::Button("Drop", ImVec2(-0.1f, 0))) {
                    std::wstring cmd = fmt::format(
                                                   L"Admincheat SpawnActorSpread \"Blueprint'/Game/Mobile/AmberDrop/AmberPickup.AmberPickup_C'\" 10 0 0 {}", AmberpickupVaule);
                    SendCheat(cmd);
                }

                static constexpr char kFloatNames[] =
                "Tek Floor\0"
                "Tek Ceiling\0"
                "Tek Pillar\0"
                "Turret Eerie\0";

                static constexpr std::array<std::wstring_view, 4> kFloatBP = {
                    L"Floor_Tek_C",
                    L"Ceiling_Tek_C",
                    L"Pillar_Tek_C",
                    L"StructureTurretEerie_BP_C"
                };

                DRGui::ArrowSelector("Float", &floatIdx, kFloatNames, ImVec2(150.0f, 0.0f), false);

                ImGui::SameLine();

                if (DRGui::Button("Build", ImVec2(-0.1f, 0))) {
                    const std::wstring_view bp = kFloatBP[static_cast<size_t>(floatIdx)];

                    std::wstring cmd = fmt::format(
                                                   L"admincheat SpawnActorSpread \"{}\" 10 0 0 1 | admincheat GiveToMe",
                                                   bp
                                                   );

                    SendCheat(cmd);
                }

                ImGui::Separator();

            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(1, 1));
            ImGui::BeginChild("adm_cmd", ImVec2(0, 1 * GroupHeight / 2), ImGuiChildFlags_Borders, ImGuiWindowFlags_NoBackground);
            {
                ImGui::PopStyleVar();

                ImGui::PushFont(NULL, style.FontSizeBase * 1.5f);
                ImGui::Text("Common");
                ImGui::Spacing();
                ImGui::PopFont();

                ImGui::Columns(2, nullptr, false);
                if (DRGui::Button("Teleport", ImVec2(-0.1f, 0))) {
                    UIAlertController* alert =
                    [UIAlertController alertControllerWithTitle:@"Tp"
                                                        message:@"Enter target coordinates"
                                                 preferredStyle:UIAlertControllerStyleAlert];

                    auto cfgTF = ^(UITextField* tf, NSString* ph) {
                        tf.placeholder = ph;
                        tf.keyboardType = UIKeyboardTypeNumbersAndPunctuation;
                        tf.autocorrectionType = UITextAutocorrectionTypeNo;
                        tf.autocapitalizationType = UITextAutocapitalizationTypeNone;
                        tf.clearButtonMode = UITextFieldViewModeWhileEditing;
                    };

                    [alert addTextFieldWithConfigurationHandler:^(UITextField* tf){ cfgTF(tf, @"X"); }];
                    [alert addTextFieldWithConfigurationHandler:^(UITextField* tf){ cfgTF(tf, @"Y"); }];
                    [alert addTextFieldWithConfigurationHandler:^(UITextField* tf){ cfgTF(tf, @"Z"); }];

                    UIAlertAction* enter =
                    [UIAlertAction actionWithTitle:@"Enter" style:UIAlertActionStyleDefault handler:^(UIAlertAction*) {
                        std::wstring sx = wtrim(ConvertUtils::convert(alert.textFields[0].text));
                        std::wstring sy = wtrim(ConvertUtils::convert(alert.textFields[1].text));
                        std::wstring sz = wtrim(ConvertUtils::convert(alert.textFields[2].text));

                        double x, y, z;
                        if (!parseDoubleW(sx, x) || !parseDoubleW(sy, y) || !parseDoubleW(sz, z)) {
                            iOS::ShowAlert(@"Invalid value", @"Enter valid numbers for X, Y, and Z.", @"OK", nullptr, nullptr);
                            return;
                        }

                        SendCheatFmt(L"cheat SetPlayerPos {} {} {}", x, y, z);
                    }];
                    [alert addAction:enter];

                    UIAlertAction* cancel = [UIAlertAction actionWithTitle:@"Cancel" style:UIAlertActionStyleCancel handler:nil];
                    [alert addAction:cancel];

                    dispatch_async(dispatch_get_main_queue(), ^{
                        UIWindow* keyWindow = UIApplication.sharedApplication.windows.firstObject;
                        if (keyWindow) {
                            UIViewController* rootViewController = keyWindow.rootViewController;
                            if (rootViewController) {
                                [rootViewController presentViewController:alert animated:YES completion:nil];
                            }
                        }
                    });
                } ImGui::NextColumn();

                if (DRGui::Button("Shutdown", ImVec2(-0.1f, 0))) {
                    SendCheat(L"cheat DoExit");
                }ImGui::NextColumn();

                if (DRGui::Button("Give To Me", ImVec2(-0.1f, 0))) {
                    SendCheat(L"cheat GiveToMe");
                }ImGui::NextColumn();

                if (DRGui::Button("Fly", ImVec2(-0.1f, 0))) {
                    SendCheat(L"cheat Fly");
                }ImGui::NextColumn();

                if (DRGui::Button("Walk", ImVec2(-0.1f, 0))) {
                    SendCheat(L"cheat Walk");
                }ImGui::NextColumn();

                if (DRGui::Button("Set Slomo", ImVec2(-0.1f, 0))) {
                    PromptInt(@"Set Slomo", @"Number", L"Slomo");
                }
                ImGui::NextColumn();



                auto buttonAndExecuteCommand = [&](const char* buttonName, const wchar_t* command, bool adminCheat = false) {
                    if (DRGui::Button(buttonName, ImVec2(-0.1f, 0))) {
                        SendCheat(command, adminCheat);
                    }
                    ImGui::NextColumn();
                };

                buttonAndExecuteCommand("PvP", L"SwitchRules PvP", true);
                buttonAndExecuteCommand("PvE", L"SwitchRules PvE", true);
                buttonAndExecuteCommand("PvX", L"SwitchRules PvX_Zone", true);
                buttonAndExecuteCommand("Pvxc", L"SwitchRules PvX_Clock", true);
                buttonAndExecuteCommand("Lock Transfer", L"LockServerTransfer", true);
                buttonAndExecuteCommand("Unlock Transfer", L"UnlockServerTransfer", true);
                buttonAndExecuteCommand("Wipe Tribe Structure", L"cheat DestroyTribeStructures");
                buttonAndExecuteCommand("Wipe Tribe Dino", L"cheat DestroyTribeDinos");
                buttonAndExecuteCommand("Take All Structure", L"cheat TakeAllStructure");
                buttonAndExecuteCommand("Take All Dino", L"cheat TakeAllDino");
                buttonAndExecuteCommand("Force Tribe", L"cheat ForcePlayerToJoinTargetTribe 0");
                buttonAndExecuteCommand("Leave Me Alone", L"cheat LeaveMeAlone");
                buttonAndExecuteCommand("Kill Tribe Player", L"cheat DestroyTribePlayers");
                buttonAndExecuteCommand("Make Tribe Admin", L"cheat MakeTribeAdmin");
                buttonAndExecuteCommand("Make Tribe Founder", L"cheat MakeTribeFounder");
                buttonAndExecuteCommand("Delete Amber", L"DestroyMyThdkget");
                buttonAndExecuteCommand("Enemy Invisible", L"EnemyInvisible true");
                buttonAndExecuteCommand("Infinite Weight", L"cheat infiniteweight");
                buttonAndExecuteCommand("Equipment Durability", L"cheat AddEquipmentDurability 99999");
                buttonAndExecuteCommand("Reset Level", L"cheat DoRestartLevel");

                ImGui::Columns(1);



                ImGui::Spacing();
                ImGui::PushFont(NULL, style.FontSizeBase * 1.5f);
                ImGui::Text("Hot Spot Server");
                ImGui::Spacing();
                ImGui::PopFont();

                ImGui::Columns(2, nullptr, false);

                auto buttonAndTeleport = [&](const char* buttonName, int x, int y, int z) {
                    if (DRGui::Button(buttonName, ImVec2(-0.1f, 0))) {
                        SendCheatFmt(L"cheat SetPlayerPos {} {} {}", x, y, z);
                    }
                    ImGui::NextColumn();
                };

                buttonAndTeleport("White Platform", 120, 108, 10);
                buttonAndTeleport("Red Ark", 80, 18, 10);
                buttonAndTeleport("Green Ark", 59, 70, 10);
                buttonAndTeleport("Blue Ark", 25, 26, 10);
                buttonAndTeleport("Ruins Of Woods", 60, 40, 10);
                buttonAndTeleport("Big Snow Cave", 29, 32, 10);
                buttonAndTeleport("Southern Cave", 80, 52, 10);
                buttonAndTeleport("Lava Cave", 70, 83, 10);
                buttonAndTeleport("Poison Cave", 62, 37, 10);
                buttonAndTeleport("Small Snow Cave", 19, 20, 10);
                buttonAndTeleport("Volcanic Cave", 41, 46, 10);
                buttonAndTeleport("Volcanic", 42, 40, 10);
                buttonAndTeleport("Volcanic Underground", 42, 39, -56000);

                ImGui::Columns(1);
            } ImGui::EndChild();
        }
            break;
        case SubPage::More:
        {
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(1, 1));
            ImGui::BeginChild("adm_more", ImVec2(0, 9 * GroupHeight / 10), ImGuiChildFlags_Borders, ImGuiWindowFlags_NoBackground);
            {
                ImGui::PopStyleVar();

                ImGui::PushFont(NULL, style.FontSizeBase * 1.5f);
                ImGui::Text("Dino Packs");
                ImGui::Spacing();
                ImGui::PopFont();

                ImGui::Columns(2, nullptr, false);

                auto spawnDinoButton = [&](const char* buttonName, const wchar_t* command) {
                    if (DRGui::Button(buttonName, ImVec2(-0.1f, 0))) {
                        SendCheat(command);
                    }
                    ImGui::NextColumn();
                };

                spawnDinoButton("Argentavis 1", L"cheat SpawnActorTamed \"Blueprint'/Game/PrimalEarth/Dinos/Argentavis/Argent_Character_BP.Argent_Character_BP_C'\" 10 0 0 | SetTargetDinoColor 0 1 | SetTargetDinoColor 1 5 | SetTargetDinoColor 2 3 | ForceTame");
                spawnDinoButton("Argentavis 2", L"cheat SpawnActorTamed \"Blueprint'/Game/PrimalEarth/Dinos/Argentavis/Argent_Character_BP.Argent_Character_BP_C'\" 10 0 0 | SetTargetDinoColor 0 5 | SetTargetDinoColor 1 1 | SetTargetDinoColor 2 7");
                spawnDinoButton("Argentavis 3", L"cheat SpawnActorTamed \"Blueprint'/Game/PrimalEarth/Dinos/Argentavis/Argent_Character_BP.Argent_Character_BP_C'\" 10 0 0 | SetTargetDinoColor 0 5 | SetTargetDinoColor 1 3 | SetTargetDinoColor 2 1");
                spawnDinoButton("Argentavis 4", L"cheat SpawnActorTamed \"Blueprint'/Game/PrimalEarth/Dinos/Argentavis/Argent_Character_BP.Argent_Character_BP_C'\" 10 0 0 | SetTargetDinoColor 0 3 | SetTargetDinoColor 1 1 | SetTargetDinoColor 2 5");
                spawnDinoButton("Titanosaur", L"cheat SpawnActorTamed \"Blueprint'/Game/PrimalEarth/Dinos/titanosaur/Titanosaur_Character_BP.Titanosaur_Character_BP_C'\" 10 0 0 | SetTargetDinoColor 0 1 | SetTargetDinoColor 2 5 | SetTargetDinoColor 1 1");
                spawnDinoButton("Griffin 1", L"cheat SpawnActorTamed \"Blueprint'/Game/PrimalEarth/Dinos/Griffin/Griffin_Character_BP.Griffin_Character_BP_C'\" 10 0 0 | SetTargetDinoColor 0 1 | SetTargetDinoColor 2 1 | SetTargetDinoColor 1 3");
                spawnDinoButton("Griffin 2", L"cheat SpawnActorTamed \"Blueprint'/Game/PrimalEarth/Dinos/Griffin/Griffin_Character_BP.Griffin_Character_BP_C'\" 10 0 0 | SetTargetDinoColor 0 3 | SetTargetDinoColor 2 6 | SetTargetDinoColor 1 1");
                spawnDinoButton("Raptor", L"cheat SpawnActorTamed \"Blueprint'/Game/PrimalEarth/Dinos/Raptor/Raptor_Character_BP.Raptor_Character_BP_C'\" 10 0 0 | SetTargetDinoColor 0 4 | SetTargetDinoColor 1 3 | SetTargetDinoColor 2 1");
                spawnDinoButton("Quetzal 1", L"cheat SpawnActorTamed \"Blueprint'/Game/PrimalEarth/Dinos/Quetzalcoatlus/Quetz_Character_BP.Quetz_Character_BP_C'\" 10 0 0 | SetTargetDinoColor 0 18 | SetTargetDinoColor 2 18 | SetTargetDinoColor 1 18");
                spawnDinoButton("Quetzal 2", L"cheat SpawnActorTamed \"Blueprint'/Game/PrimalEarth/Dinos/Quetzalcoatlus/Quetz_Character_BP.Quetz_Character_BP_C'\" 10 0 0 | SetTargetDinoColor 0 3 | SetTargetDinoColor 2 6 | SetTargetDinoColor 1 1");
                spawnDinoButton("Gigan 1", L"cheat SpawnActorTamed \"Blueprint'/Game/PrimalEarth/Dinos/Giganotosaurus/Gigant_Character_BP.Gigant_Character_BP_C'\" 10 0 0 | SetTargetDinoColor 0 3 | SetTargetDinoColor 2 6 | SetTargetDinoColor 1 1");
                spawnDinoButton("Gigan 2", L"cheat SpawnActorTamed \"Blueprint'/Game/PrimalEarth/Dinos/Giganotosaurus/Gigant_Character_BP.Gigant_Character_BP_C'\" 10 0 0 | SetTargetDinoColor 0 5 | SetTargetDinoColor 2 5 | SetTargetDinoColor 1 5");
                spawnDinoButton("Rex 1", L"cheat SpawnActorTamed \"Blueprint'/Game/PrimalEarth/Dinos/Rex/Rex_Character_BP.Rex_Character_BP_C'\" 10 0 0 | SetTargetDinoColor 0 5 | SetTargetDinoColor 2 5 | SetTargetDinoColor 1 4");
                spawnDinoButton("Rex 2", L"cheat SpawnActorTamed \"Blueprint'/Game/PrimalEarth/Dinos/Rex/Rex_Character_BP.Rex_Character_BP_C'\" 10 0 0 | SetTargetDinoColor 0 4 | SetTargetDinoColor 2 3 | SetTargetDinoColor 1 2");
                spawnDinoButton("Carno", L"cheat SpawnActorTamed \"Blueprint'/Game/PrimalEarth/Dinos/Carno/Carno_Character_BP.Carno_Character_BP_C'\" 10 0 0 | SetTargetDinoColor 0 2 | SetTargetDinoColor 1 3 | SetTargetDinoColor 2 1");
                spawnDinoButton("Therizinosaur", L"cheat SpawnActorTamed \"Blueprint'/Game/PrimalEarth/Dinos/Therizinosaurus/Therizino_Character_BP.Therizino_Character_BP_C'\" 10 0 0 | SetTargetDinoColor 0 4 | SetTargetDinoColor 1 6 | SetTargetDinoColor 2 3");
                spawnDinoButton("Spino", L"cheat SpawnActorTamed \"Blueprint'/Game/PrimalEarth/Dinos/Spino/Spino_Character_BP.Spino_Character_BP_C'\" 10 0 0 | SetTargetDinoColor 0 18 | SetTargetDinoColor 1 18 | SetTargetDinoColor 2 18");

                ImGui::Columns(1);



                ImGui::Spacing();
                ImGui::PushFont(NULL, style.FontSizeBase * 1.5f);
                ImGui::Text("Dungeon Spawn");
                ImGui::Spacing();
                ImGui::PopFont();

                ImGui::Columns(2, nullptr, false);
                DRGui::CheckBox("Spawn Map", &SpawnDung);
                ImGui::NextColumn();
                DRGui::CheckBox("Destroy Map", &DestroyDung);
                ImGui::Columns(1);
                ImGui::Separator();  // Gạch Ngang

                ImGui::Columns(2, nullptr, false);  // 2 columns, without borders

                auto processButtonCommand = [&](const char* buttonName, const wchar_t* spawnPath, const wchar_t* destroyName) {
                    if (DRGui::Button(buttonName, ImVec2(-0.1f, 0))) {
                        std::wstring cmd;

                        if (SpawnDung) {
                            cmd = fmt::format(L"cheat SpawnActor \"{}\" 10 0 0", spawnPath);
                        } else if (DestroyDung) {
                            cmd = fmt::format(L"Admincheat destroyall {}", destroyName);
                        } else {
                            ImGui::NextColumn();
                            return;
                        }

                        SendCheat(cmd);
                    }

                    ImGui::NextColumn();
                };

                processButtonCommand("Boss Arena", L"Blueprint'/Game/Mobile/Dungeon/BossArena/BossArena.BossArena_C'", L"BossArena_C");
                processButtonCommand("Noctis Map", L"Blueprint'/Game/Mobile/Dungeon/BossArena/Obstacles/AnticornObstacle.AnticornObstacle_C'", L"AnticornObstacle_C");
                processButtonCommand("Argentustus Map", L"Blueprint'/Game/Mobile/Dungeon/BossArena/Obstacles/ArgentObstacle.ArgentObstacle_C'", L"ArgentObstacle_C");
                processButtonCommand("Broodmother Map", L"Blueprint'/Game/Mobile/Dungeon/BossArena/Obstacles/BroodmotherObstacle.BroodmotherObstacle_C'", L"BroodmotherObstacle_C");
                processButtonCommand("Obsidioequus Map", L"Blueprint'/Game/Mobile/Dungeon/BossArena/Obstacles/ChalicoObstacle.ChalicoObstacle_C'", L"ChalicoObstacle_C");
                processButtonCommand("Cnidaria Map", L"Blueprint'/Game/Mobile/Dungeon/BossArena/Obstacles/CnidariaObstacle.CnidariaObstacle_C'", L"CnidariaObstacle_C");
                processButtonCommand("Dodobitus Map", L"Blueprint'/Game/Mobile/Dungeon/BossArena/Obstacles/DodoObstacle.DodoObstacle_C'", L"DodoObstacle_C");
                processButtonCommand("Doedicurus Map", L"Blueprint'/Game/Mobile/Dungeon/BossArena/Obstacles/Doed_Obstacle.Doed_Obstacle_C'", L"Doed_Obstacle_C");
                processButtonCommand("Dung Beetle Map", L"Blueprint'/Game/Mobile/Dungeon/BossArena/Obstacles/DungBeetleObstacle.DungBeetleObstacle_C'", L"DungBeetleObstacle_C");
                processButtonCommand("Gorilla Map", L"Blueprint'/Game/Mobile/Dungeon/BossArena/Obstacles/GorillaObstacle.GorillaObstacle_C'", L"GorillaObstacle_C");
                processButtonCommand("Toed Map", L"Blueprint'/Game/Mobile/Dungeon/BossArena/Obstacles/ToadObstacle.ToadObstacle_C'", L"ToadObstacle_C");

                ImGui::Columns(1);
            } ImGui::EndChild();
        }
            break;
        default:
            break;

    }
}

/* * * * * *  Admin Header End   * * * * * */
