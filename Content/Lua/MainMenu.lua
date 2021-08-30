
local LuaTestCase=import('LuaTestCase');
local KismetStringLibrary = import('KismetStringLibrary');
local KismetSystemLibrary = import('KismetSystemLibrary')
local WidgetBlueprintFunctionLibrary = import('WidgetBlueprintFunctionLibrary');
local GameplayStatics = import("GameplayStatics");
local stringType = UEnums.EPropertyClass.Str
local LuaTestCaseInstance = LuaTestCase();

--所有回调函数------------------------------------------------------
function LuaCallFunction(functionName)
    print("test")
end

function LuaComboBoxSwitchOptionCallback(functionName, newOption)
    local mainMenuPlayerController = LuaTestCaseInstance:GetMainMenuPlayerController()
    if LuaTestCaseInstance:IsObjectValid(mainMenuPlayerController.m_pCurRankInfo) then
        mainMenuPlayerController.m_pCurRankInfo:AskFadeOut()
        mainMenuPlayerController.m_curRankListMapType = newOption
    end
end

function LuaButtonClickCallback(buttonFunction)
    local mainMenuPlayerController = LuaTestCaseInstance:GetMainMenuPlayerController()
    if buttonFunction == "Button_RankMenu_Resume" then
        mainMenuPlayerController.m_nextMenuName = "MainMenu"
        mainMenuPlayerController.m_pRankMenu:AskMenuFadeOut()
    elseif buttonFunction == "Button_RuneMenu_Resume" then
        mainMenuPlayerController.m_nextMenuName = "MainMenu"
        mainMenuPlayerController.m_pRuneMenu:AskMenuFadeOut()
    elseif buttonFunction == "Button_NotificationShowHide" then
        print("MainMenu::LuaButtonClickCallback notification show hide")
        mainMenuPlayerController:LoadMenu("NotificationMenu")
    elseif buttonFunction == "Button_Notification_Resume" then
        mainMenuPlayerController.m_pNotificationMenu:AskMenuFadeOut()
    elseif buttonFunction == "Button_Notification_ClearMessages" then
        local w = WidgetBlueprintFunctionLibrary()
        w:ClearAllNotifications(mainMenuPlayerController.m_pNotificationMenu)
    elseif buttonFunction == "Button_EnsureEnterRoom" then
        local gameInstance = LuaTestCaseInstance:GetCollisionWarGameInstance()
        if gameInstance.m_accountStatus == "MatchSuccessful" then
            local mainMenuGameMode = LuaTestCaseInstance:GetMainMenuGameMode()
            mainMenuGameMode:ReqEnsureEnterRoom()
        end
    else
        local k = KismetStringLibrary()
        if k:Contains(buttonFunction, "Button_Notification_", false, false) then
            DealNotification(buttonFunction)
        elseif k:Contains(buttonFunction, "Button_Rune_", false, false) then
            for i = 0, mainMenuPlayerController.m_pRuneMenu.m_pRuneElements:Num() - 1 do
                local runeElement = mainMenuPlayerController.m_pRuneMenu.m_pRuneElements:Get(i)
                local runeElementName = k:RightChop(buttonFunction, 12)
                if runeElementName == runeElement.m_runeName then
                    if mainMenuPlayerController.m_pRuneMenu.m_pSelectRuneElement == nil then
                        mainMenuPlayerController.m_pRuneMenu.m_pSelectRuneElement = mainMenuPlayerController.m_pRuneMenu.m_pRuneElements:Get(i)
                    elseif mainMenuPlayerController.m_pRuneMenu.m_pSelectRuneElement == mainMenuPlayerController.m_pRuneMenu.m_pRuneElements:Get(i) then
                        mainMenuPlayerController.m_pRuneMenu.m_pSelectRuneElement = nil
                    else
                        mainMenuPlayerController.m_pRuneMenu.m_pSelectRuneElement = mainMenuPlayerController.m_pRuneMenu.m_pRuneElements:Get(i)
                    end
                    break
                end
            end
        elseif k:Contains(buttonFunction, "Button_RuneAttribute_", false, false) then
            if mainMenuPlayerController.m_pRuneMenu.m_pSelectRuneElement ~= nil then
                if buttonFunction == "Button_RuneAttribute_Sky" then
                    mainMenuPlayerController.m_pRuneMenu:SetAttibuteRune("sky", mainMenuPlayerController.m_pRuneMenu.m_pSelectRuneElement.m_runeTag)
                elseif buttonFunction == "Button_RuneAttribute_Ground" then
                    mainMenuPlayerController.m_pRuneMenu:SetAttibuteRune("ground", mainMenuPlayerController.m_pRuneMenu.m_pSelectRuneElement.m_runeTag)
                elseif buttonFunction == "Button_RuneAttribute_Life" then
                    mainMenuPlayerController.m_pRuneMenu:SetAttibuteRune("life", mainMenuPlayerController.m_pRuneMenu.m_pSelectRuneElement.m_runeTag)
                else
                    mainMenuPlayerController.m_pRuneMenu:SetAttibuteRune("death", mainMenuPlayerController.m_pRuneMenu.m_pSelectRuneElement.m_runeTag)
                end
                mainMenuPlayerController.m_pRuneMenu:NotifyAttributeRuneChange(buttonFunction,
                        mainMenuPlayerController.m_pRuneMenu.m_pSelectRuneElement.m_runeTag)
                mainMenuPlayerController.m_pRuneMenu.m_pSelectRuneElement = nil
            else
                if buttonFunction == "Button_RuneAttribute_Sky" then
                    mainMenuPlayerController.m_pRuneMenu:SetAttibuteRune("sky", 0)
                elseif buttonFunction == "Button_RuneAttribute_Ground" then
                    mainMenuPlayerController.m_pRuneMenu:SetAttibuteRune("ground", 0)
                elseif buttonFunction == "Button_RuneAttribute_Life" then
                    mainMenuPlayerController.m_pRuneMenu:SetAttibuteRune("life", 0)
                else
                    mainMenuPlayerController.m_pRuneMenu:SetAttibuteRune("death", 0)
                end
                mainMenuPlayerController.m_pRuneMenu:NotifyAttributeRuneChange(buttonFunction, 0)
            end
        end
    end
end

function LuaInvisibleButtonClickCallback(buttonFunction, buttonLocation)
    print("MainMenu::LuaInvisibleButtonClickCallback click button: ",buttonFunction)
    local mainMenuPlayerController = LuaTestCaseInstance:GetMainMenuPlayerController()
    if buttonFunction == "Button_Battle" then
        mainMenuPlayerController.m_nextMenuName = "SelectBattleMenu"
        mainMenuPlayerController.m_pMainMenu:AskMenuFadeOut()
    elseif buttonFunction == "Button_Mall" then
        mainMenuPlayerController.m_nextMenuName = "MallMenu"
        mainMenuPlayerController.m_pMainMenu:AskMenuFadeOut()
    elseif buttonFunction == "Button_Rank" then
        print("MainMenu::LuaInvisibleButtonClickCallback click button rank")
        mainMenuPlayerController.m_nextMenuName = "RankMenu"
        mainMenuPlayerController.m_pMainMenu:AskMenuFadeOut()
    elseif buttonFunction == "Button_Rune" then
        mainMenuPlayerController.m_nextMenuName = "RuneMenu"
        mainMenuPlayerController.m_pMainMenu:AskMenuFadeOut()
    else
        local k = KismetSystemLibrary()
        local containFlag = KismetStringLibrary:Contains(buttonFunction, "Friend_", false, false)
        if containFlag == false then
            return
        end
        --说明该按键是选择朋友的按键，这是需要切换默认朋友
        mainMenuPlayerController.m_pMainMenu.m_pChatBox:SwitchCustomFriend(buttonFunction)
    end
end

function LuaMenuFadeOutDoneCallback(menuName)
    if menuName == "MainMenu" then
        local mainMenuPlayerController = LuaTestCaseInstance:GetMainMenuPlayerController()
        mainMenuPlayerController.m_pMainMenu:RemoveFromParent()
        SwitchMenu()
    elseif menuName == "RankMenu" then
        local mainMenuPlayerController = LuaTestCaseInstance:GetMainMenuPlayerController()
        mainMenuPlayerController.m_pRankMenu:RemoveFromParent()
        SwitchMenu()
    elseif menuName == "NotificationMenu" then
        local mainMenuPlayerController = LuaTestCaseInstance:GetMainMenuPlayerController()
        mainMenuPlayerController.m_pNotificationMenu:RemoveFromParent()
        LuaTestCaseInstance:DeleteObject(mainMenuPlayerController.m_pNotificationMenu)
    elseif menuName == "RuneMenu" then
        local mainMenuPlayerController = LuaTestCaseInstance:GetMainMenuPlayerController()
        mainMenuPlayerController.m_pRuneMenu:RemoveFromParent()
        SwitchMenu()
    end
end

function LuaNewNotification()
    local mainMenuPlayerController = LuaTestCaseInstance:GetMainMenuPlayerController()
    local w = WidgetBlueprintFunctionLibrary()
    w:AddNotificationToSimpleMenu(mainMenuPlayerController,
    mainMenuPlayerController.m_pMainMenu.m_pMainMenuWidgetManager.m_BPNotificationClass,
    mainMenuPlayerController.m_pMainMenu,"",50,0,0,0,0,0)
end

function LuaDealNewChatMessage(friendName, message)
    local mainMenuPlayerController = LuaTestCaseInstance:GetMainMenuPlayerController()
    local w = WidgetBlueprintFunctionLibrary()
    w:AddMessageToChatBox(mainMenuPlayerController, mainMenuPlayerController.m_pMainMenu.m_pChatBox,
    friendName, message, 50)
end

function LuaDealNewMessage(message)
    if message == "matchSuccessful" then
        --load ensure enter room menu
    elseif message == "PlayerEnterWorld" then
        local gameInstance = LuaTestCaseInstance:GetCollisionWarGameInstance()
        gameInstance.m_hasCSEnterWorld = true
    elseif message == "dispatchRankList" then
        local mainMenuPlayerController = LuaTestCaseInstance:GetMainMenuPlayerController()
        mainMenuPlayerController.m_nextMenuName = "MainMenu"
        mainMenuPlayerController:LoadRankMenu()
    elseif message == "dispatchAllRuneDataToClient" then
        local mainMenuPlayerController = LuaTestCaseInstance:GetMainMenuPlayerController()
        mainMenuPlayerController:LoadRuneMenu()
        local w = WidgetBlueprintFunctionLibrary()
        local margin = FMargin(5,5,5,5)
        print("MainMenu::LuaDealNewMessage dispatchAllRuneDataToClient")
        w:InitialRunesToRuneMenu(mainMenuPlayerController, mainMenuPlayerController.m_pRuneMenu,
                mainMenuPlayerController.m_pRuneMenu.m_pWidgetManager, margin, 50)
    elseif message == "dispatchRuneConfigEffectToClient" then
        local gameInstance = LuaTestCaseInstance:GetCollisionWarGameInstance()
        local mainMenuGameMode = LuaTestCaseInstance:GetMainMenuGameMode()
        for i = 0,mainMenuGameMode.m_curRuneConfigEffectInfo.attributeList:Num() - 1 do
            local attribute = mainMenuGameMode.m_curRuneConfigEffectInfo.attributeList:Get(i)
            if attribute == "life" then
                gameInstance.m_playerInfo.additionEffect.hpModifyPercent =
                gameInstance.m_playerInfo.additionEffect.hpModifyPercent + mainMenuGameMode.m_curRuneConfigEffectInfo.effectList:Get(i)
            elseif attribute == "ATK" then
                gameInstance.m_playerInfo.additionEffect.physAtkModifyPercent =
                gameInstance.m_playerInfo.additionEffect.physAtkModifyPercent + mainMenuGameMode.m_curRuneConfigEffectInfo.effectList:Get(i)
            elseif attribute == "magATK" then
                gameInstance.m_playerInfo.additionEffect.magAtkModifyPercent =
                gameInstance.m_playerInfo.additionEffect.magAtkModifyPercent + mainMenuGameMode.m_curRuneConfigEffectInfo.effectList:Get(i)
            elseif attribute == "DFC" then
                gameInstance.m_playerInfo.additionEffect.physDfcModifyPercent =
                gameInstance.m_playerInfo.additionEffect.physDfcModifyPercent + mainMenuGameMode.m_curRuneConfigEffectInfo.effectList:Get(i)
            elseif attribute == "magDFC" then
                gameInstance.m_playerInfo.additionEffect.magDfcModifyPercent =
                gameInstance.m_playerInfo.additionEffect.magDfcModifyPercent + mainMenuGameMode.m_curRuneConfigEffectInfo.effectList:Get(i)
            end
        end
        gameInstance.m_playerInfo.runeInfo.curRuneConfigNb = mainMenuGameMode.m_curRuneConfigEffectInfo.effectNb
    end
end

--功能函数---------------------------------------------------
function DealNotification(buttonFunction)
    local CWGameMode = LuaTestCaseInstance:GetCWGameMode()
    local functionType = ""
    local functionName = ""
    local keyWords = ""
    CWGameMode.DealNotificationButtonCallback(buttonFunction, functionType, functionName, keyWords)
    if functionType == "AddFriend" then
        if functionName == "Accept" then
            CWGameMode:ReqAnswerAddFriendRequest(true, keyWords)
        else
            CWGameMode:ReqAnswerAddFriendRequest(false, keyWords)
        end
    elseif functionType == "2Vs2Match" or functionType == "3Vs3Match" then
        if functionName == "Accept" then
            local k = KismetStringLibrary()
            local barLoc = k:FindSubString(keyWords,"/",false,false,-1)
            local hostName = k:Left(keyWords, barLoc)
            local groupNbStr = k:RightChop(keyWords, barLoc + 1)
            local groupNb = k:Conv_StringToInt(groupNbStr)
            CWGameMode:ReqAnswerFriendMatch(true, hostName, "", groupNb)
            local g = GameplayStatics()
            g:OpenLevel(CWGameMode, "SelectBattleMap", true, "")
        else
            CWGameMode:ReqAnswerFriendMatch(false, keyWords, "", 0)
        end
    end
end


function SwitchMenu()
    local mainMenuPlayerController = LuaTestCaseInstance:GetMainMenuPlayerController()
    if mainMenuPlayerController.m_nextMenuName == "MallMenu" then
        local gameInstance = LuaTestCaseInstance:GetCollisionWarGameInstance()
        gameInstance.m_curLevelName = "PreBattleMap"
        local g = GameplayStatics()
        g:OpenLevel(mainMenuPlayerController, "PreBattleMap", true, "")
    elseif mainMenuPlayerController.m_nextMenuName == "SelectBattleMenu" then
        local g = GameplayStatics()
        g:OpenLevel(mainMenuPlayerController, "SelectBattleMap", true, "")
    elseif mainMenuPlayerController.m_nextMenuName == "RankMenu" then
        local mainMenuGameMode = LuaTestCaseInstance:GetMainMenuGameMode()
        mainMenuGameMode:ReqRankList()
    elseif mainMenuPlayerController.m_nextMenuName == "MainMenu" then
        mainMenuPlayerController:LoadMenu("MainMenu")
    elseif mainMenuPlayerController.m_nextMenuName == "RuneMenu" then
        local mainMenuGameMode = LuaTestCaseInstance:GetMainMenuGameMode()
        mainMenuGameMode:ReqAllRuneDataFromServer()
    end
end



