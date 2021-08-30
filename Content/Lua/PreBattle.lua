
local LuaTestCase=import('LuaTestCase');
local KismetStringLibrary = import('KismetStringLibrary');
local KismetSystemLibrary = import('KismetSystemLibrary');
local WidgetBlueprintFunctionLibrary = import('WidgetBlueprintFunctionLibrary');
local GameplayStatics = import("GameplayStatics")
local stringType = UEnums.EPropertyClass.Str
local LuaTestCaseInstance = LuaTestCase();

--所有回调函数------------------------------------------------------
function TestMenu()
    local pc = LuaTestCaseInstance:GetPreBattlePlayerController()
    print(pc.m_pPreBattleMenu.m_pCurScrollBox.m_scrollBoxCaption)
end

function LuaCallFunction(functionName)
    if functionName == "TestMenu" then
        TestMenu()
    end
end

function LuaButtonClickCallback(buttonFunction)
    local preBattlePlayerController = LuaTestCaseInstance:GetPreBattlePlayerController()
    if buttonFunction == "Button_Resume_PlayerState" then
        preBattlePlayerController.m_pPlayerStatusMenu:AskFadeOut()
    elseif buttonFunction == "Button_Resume_Charge" then
        preBattlePlayerController.m_pChargeMenu:AskMenuFadeOut()
    elseif buttonFunction == "Button_FriendList_Resume" then
        preBattlePlayerController.m_pFriendListMenu:AskMenuFadeOut()
    elseif buttonFunction == "Button_FriendList_SearchPlayer" then
        local preBattleGameMode = LuaTestCaseInstance:GetPreBattleGameMode()
        local friendNameList = slua.Array(stringType)
        friendNameList:Add(preBattlePlayerController.m_pFriendListMenu.m_searchFriendName)
        preBattleGameMode:ReqPlayerTagInfoList(friendNameList)
    elseif buttonFunction == "Button_FriendList_AddFriend" then
        local canAddFlag = preBattlePlayerController:TellWhetherCanAddFriend()
        if canAddFlag == true then
            local preBattleGameMode = LuaTestCaseInstance:GetPreBattleGameMode()
            preBattleGameMode:ReqAddFriend(preBattlePlayerController.m_pFriendListMenu.m_searchFriendName)
        end
    elseif buttonFunction == "Button_NotificationShowHide" then
        preBattlePlayerController:LoadNotificationMenu()
    elseif buttonFunction == "Button_Notification_Resume" then
        preBattlePlayerController.m_pNotificationMenu:AskMenuFadeOut()
    elseif buttonFunction == "Button_Notification_ClearMessages" then
        local w = WidgetBlueprintFunctionLibrary()
        w:ClearAllNotifications(preBattlePlayerController.m_pNotificationMenu)
    elseif buttonFunction == "Button_EnsureEnterRoom" then
        local gameInstance = LuaTestCaseInstance:GetCollisionWarGameInstance()
        if gameInstance.m_accountStatus == "MatchSuccessful" then
            local preBattleGameMode = LuaTestCaseInstance:GetPreBattleGameMode()
            preBattleGameMode:ReqEnsureEnterRoom()
        end
    elseif buttonFunction == "Button_SkillTreeMenuResume" then
        preBattlePlayerController.m_pSkillTreeMenu:AskFadeOut()
    elseif buttonFunction == "Button_CharacterStatusResume" then
        preBattlePlayerController.m_pCharacterStatusMenu:AskFadeOut()
    else
        local k = KismetStringLibrary()
        if k:Contains(buttonFunction, "Button_PlayerTag_", false, false) == true then
            preBattlePlayerController.m_pFriendListMenu:SwitchPlayerInfo(buttonFunction)
        elseif k:Contains(buttonFunction, "Button_Notification_", false, false) == true then
            DealNotification(buttonFunction)
        end
    end
end


function LuaInvisibleButtonClickCallback(buttonFunction, buttonLocation)
    local preBattlePlayerController = LuaTestCaseInstance:GetPreBattlePlayerController()
    if buttonLocation == 1 then
        -- 1就是ScrollMenu_PreBattleMenu
        preBattlePlayerController.m_pPreBattleMenu:SwitchCustomScrollButton(buttonFunction, 50, 0,0,0,0,0,400)
    elseif buttonLocation == 2 then
        -- 2就是TopMenu_PreBattleMenu
        preBattlePlayerController.m_pPreBattleMenu:SwitchCustomTopMenuButton(buttonFunction)
        -- SwitchCustomTopMenu会触发ScrollBoxFadeOut函数，所以切换scrollBox的实现在FadeOutDone回调处
        if buttonFunction == "Button_PlayerState" then
            preBattlePlayerController:LoadPlayerStatusMenu()
        elseif buttonFunction == "Button_FriendList" then
            preBattlePlayerController:LoadFriendListMenu()
        elseif buttonFunction == "Button_Charge" then
            preBattlePlayerController:LoadChargeMenu()
        elseif buttonFunction == "Button_SetLastSelectCharacter" then
            local preBattleGameMode = LuaTestCaseInstance:GetPreBattleGameMode()
            preBattleGameMode:ReqChangeCurSelectCharacter()
        elseif buttonFunction == "Button_LoadCharacterSkillTree" then
            preBattlePlayerController:LoadSkillTreeMenu(preBattlePlayerController.m_pPreBattleMenu.m_curCharacterName)
        elseif buttonFunction == "Button_LoadCharacterStatus" then
            preBattlePlayerController:LoadCharacterStateMenu()
        elseif buttonFunction == "Button_BackToMainMenu" then
            preBattlePlayerController.m_pPreBattleMenu:AskFadeOut()
        end
    elseif buttonLocation == 3 then
        -- 3就是Others_PreBattleMenu
        print("PreBattle::LuaInvisibleButtonClickCallback click player tag")
        local k = KismetStringLibrary()
        if k:Contains(buttonFunction, "Friend_", false, false) == true then
            preBattlePlayerController.m_pPreBattleMenu.m_pChatBox:SwitchCustomFriend(buttonFunction)
        end
    end
end

function LuaPlayerTagClick(buttonFunction)

end

function LuaMenuFadeOutDoneCallback(menuName)
    local preBattlePlayerController = LuaTestCaseInstance:GetPreBattlePlayerController()
    if menuName == "PlayerStateMenu" then
        preBattlePlayerController.m_pPlayerStatusMenu:RemoveFromParent()
    elseif menuName == "FriendListMenu" then
        preBattlePlayerController.m_pFriendListMenu:RemoveFromParent()
    elseif menuName == "ChargeMenu" then
        preBattlePlayerController.m_pChargeMenu:RemoveFromParent()
    elseif menuName == "PreBattleMenu" then
        preBattlePlayerController.m_pPreBattleMenu:RemoveFromParent()
        local g= GameplayStatics()
        g:OpenLevel(preBattlePlayerController, "MainMenuMap", true, "")
    elseif menuName == "SkillTreeMenu" then
        preBattlePlayerController.m_pSkillTreeMenu:RemoveFromParent()
        preBattlePlayerController.m_pSkillTreeMenu = nil
    elseif menuName == "CharacterStatusMenu" then
        preBattlePlayerController.m_pCharacterStatusMenu:RemoveFromParent()
        preBattlePlayerController.m_pCharacterStatusMenu = nil
    elseif menuName == "NotificationMenu" then
        preBattlePlayerController.m_pNotificationMenu:RemoveFromParent()
        LuaTestCaseInstance:DeleteObject(preBattlePlayerController.m_pNotificationMenu)
    end
end

function LuaElementFadeOutDoneCallback(caption)
    local preBattlePlayerController = LuaTestCaseInstance:GetPreBattlePlayerController()
    preBattlePlayerController.m_pPreBattleMenu.m_isContentScrollBoxFading = false
    preBattlePlayerController.m_pPreBattleMenu:ScrollBoxFadeOutDone(caption)
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
    if message == "NotifyInitialDone" then
        --load ensure enter room menu
        print("PreBattle::LuaDealNewMessage deal new messge initial done")
        local preBattlePlayerController = LuaTestCaseInstance:GetPreBattlePlayerController()
        if LuaTestCaseInstance:IsObjectValid(preBattlePlayerController.m_pLoadMenu) == true then
            preBattlePlayerController.m_pLoadMenu:RemoveFromParent()
            LuaTestCaseInstance:DeleteObject(preBattlePlayerController.m_pLoadMenu)
        else
            print("PreBattle::LuaDealNewMessage load menu is not valid")
        end
        print("PreBattle::LuaDealNewMessage load prebattle menu")
        preBattlePlayerController:LoadPreBattleMenu()
    elseif message == "matchSuccessful" then
        local preBattlePlayerController = LuaTestCaseInstance:GetPreBattlePlayerController()
        preBattlePlayerController:LoadEnsureEnterRoomMenu()
    elseif message == "PlayerEnterWorld" then
        local gameInstance = LuaTestCaseInstance:GetCollisionWarGameInstance()
        gameInstance.m_hasCSEnterWorld = true
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
            local g= GameplayStatics()
            g:OpenLevel(CWGameMode, "SelectBattleMap", true, "")
        else
            CWGameMode:ReqAnswerFriendMatch(false, keyWords, "", 0)
        end
    end
end





--[[
print("hello world")


xx={}
function xx.text(v)
    print("xx.text",v)
end

function bpcall(a,b,c,d)
    --print("call from bp",a,b,c,d)
    return 1024,"return from lua 虚幻引擎"
end

local HitResult = import('HitResult');
local tt=0
local ret={1,2,3,4,5}
function update(dt,actor)
    tt=tt+dt
    local p = actor:K2_GetActorLocation()
    local h = HitResult()
    local v = FVector(math.sin(tt)*100,2,3)
    local offset = FVector(0,math.cos(tt)*50,0)
    local ok,h=actor:K2_SetActorLocation(v+offset,true,h,true)

    collectgarbage("collect")
    return 1024,2,"s",ret,function() end
end

function implementSkill(skillName, actor)
    if skillName == "kouxue"
    then
        local actorLoc = actor:K2_GetActorLocation()
        local offset = FVector(100,0,0)
        actorLoc = offset + actorLoc
        local h = HitResult()
        actor:K2_SetActorLocation(actorLoc, true, h, true)
    end
    print("slua::implementSkill slua has implement skill")
end

function setPCTestVal(pc)
    print("slua::setPCTestVal slua has change m_luaTestVal")
    pc.m_luaTestVal = pc.m_luaTestVal+1
end

return 1024

]]