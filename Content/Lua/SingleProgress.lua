---
--- Generated by EmmyLua(https://github.com/EmmyLua)
--- Created by Administrator.
--- DateTime: 2018/12/29 17:45
---
local LuaTestCase=import('LuaTestCase');
local KismetStringLibrary = import('KismetStringLibrary');
local KismetSystemLibrary = import('KismetSystemLibrary');
local WidgetBlueprintFunctionLibrary = import('WidgetBlueprintFunctionLibrary');
local CollisionWarBpFunctionLibrary = import('CollisionWarBpFunctionLibrary')
local GameplayStatics = import("GameplayStatics")
local stringType = UEnums.EPropertyClass.Str
local L = LuaTestCase();
local BPF = CollisionWarBpFunctionLibrary()


function LuaButtonClickCallback(buttonFunction)
    local k = KismetStringLibrary()
    if buttonFunction == "Button_CardInfo" then
        local singleProgressPC = L:GetSingleProgressPlayerController()
        singleProgressPC:LoadCardInfoMenu()
    elseif buttonFunction == "Button_SkillIcon_BasicCardInfo" then
        local singleProgressPC = L:GetSingleProgressPlayerController()
        singleProgressPC.m_nextMenuName = "SkillTree"
        singleProgressPC.m_pCardInfoMenu:NotifyFadeOut()
    elseif buttonFunction == "Button_Calendar" then
        local singleProgressPC = L:GetSingleProgressPlayerController()
        singleProgressPC:LoadCalendarMenu()
    elseif buttonFunction == "Button_CharacterInfo" then
        local singleProgressPC = L:GetSingleProgressPlayerController()
    elseif buttonFunction == "Button_HistoryInfo" then
        local singleProgressPC = L:GetSingleProgressPlayerController()
    elseif buttonFunction == "Button_Intelligence" then
        local singleProgressPC = L:GetSingleProgressPlayerController()
    elseif buttonFunction == "Button_Progress" then
        print(buttonFunction)
        local singleProgressGameMode = L:GetSingleProgressGameMode()
        singleProgressGameMode:ProceedNextGame()
    elseif buttonFunction == "Button_CardInfoMenuCancel" then
        local singleProgressPC = L:GetSingleProgressPlayerController()
        singleProgressPC.m_nextMenuName = "NULL"
        singleProgressPC.m_pCardInfoMenu:NotifyFadeOut()
    elseif buttonFunction == "Button_SkillTreeMenuCancel" then
        local singleProgressPC = L:GetSingleProgressPlayerController()
        singleProgressPC.m_nextMenuName = "NULL"
        singleProgressPC.m_pSkillTree:NotifyFadeOut()
    elseif buttonFunction == "Button_SkillTreeMenuToCardInfoMenu" then
        local singleProgressPC = L:GetSingleProgressPlayerController()
        singleProgressPC.m_nextMenuName = "CardInfoMenu"
        singleProgressPC.m_pSkillTree:NotifyFadeOut()
    elseif k:Contains(buttonFunction, "Button_SkillIcon_", false, false) then
        local skillName = k:RightChop(buttonFunction, 17)
        local singleProgressPC = L:GetSingleProgressPlayerController()
        local w = WidgetBlueprintFunctionLibrary()
        w:AddGeneralCardToDetailsPanel(singleProgressPC.m_pSkillTree, skillName)
        singleProgressPC.m_pSkillTree:SetCurSkillIcon(skillName)
    end
end

function LuaMenuFadeOutDoneCallback(menuName)
    if menuName == "CardInfoMenu" then
        local singleProgressPC = L:GetSingleProgressPlayerController()
        singleProgressPC:DeleteCardInfoMenu()
        if singleProgressPC.m_nextMenuName == "SkillTree" then
            singleProgressPC:LoadSkillTree()
        end
    elseif menuName == "SkillTree" then
        local singleProgressPC = L:GetSingleProgressPlayerController()
        singleProgressPC:DeleteSkillTreeMenu()
        if singleProgressPC.m_nextMenuName == "CardInfoMenu" then
            singleProgressPC:LoadCardInfoMenu()
        end
    end
end

function LuaMenuFadeInDoneCallback(menuName)
    if menuName == "DecipherMenu" then
        local decipherGameMode = L:GetDecipherGameMode()
        decipherGameMode:InterludeParticle("InterludeAction")
    end
end
