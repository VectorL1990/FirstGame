
local LuaTestCase=import('LuaTestCase');
local KismetStringLibrary = import('KismetStringLibrary');
local WidgetBlueprintFunctionLibrary = import('WidgetBlueprintFunctionLibrary');
local GameplayStatics = import("GameplayStatics")
local stringType = UEnums.EPropertyClass.Str
local LuaTestCaseInstance = LuaTestCase();
local HitResult = import('HitResult');

--所有回调函数------------------------------------------------------


function LuaButtonClickCallback(buttonFunction)
    local chooseMapPlayerController = LuaTestCaseInstance:GetChooseMapPlayerController()
    if buttonFunction == "Button_NotificationShowHide" then
        chooseMapPlayerController:LoadNotificationMenu()
    elseif buttonFunction == "Button_Notification_Resume" then
        chooseMapPlayerController.m_pNotificationMenu:AskMenuFadeOut()
    elseif buttonFunction == "Button_Notification_ClearMessages" then
        WidgetBlueprintFunctionLibrary:ClearAllNotifications(chooseMapPlayerController.m_pNotificationMenu)
    elseif buttonFunction == "Button_EnsureEnterRoom" then
        local gameInstance = LuaTestCaseInstance:GetCollisionWarGameInstance()
        if gameInstance.m_accountStatus == "MatchSuccessful" then
            local chooseMapGameMode = LuaTestCaseInstance:GetChooseMapGameMode()
            chooseMapGameMode:ReqEnsureEnterRoom()
        end
    elseif buttonFunction == "Button_SelectFriend_Resume" then
        chooseMapPlayerController.m_pSelectFriendMenu:AskFadeOut()
    else
        local k = KismetStringLibrary()
        if k:Contains(buttonFunction, "Button_PlayerTag_", false, false) == true then
            chooseMapPlayerController.m_pSelectFriendMenu:SwitchPlayerInfo(buttonFunction)
        elseif k:Contains(buttonFunction, "Button_SelectPlayer_", false, false) == true then
            chooseMapPlayerController.m_pSelectFriendMenu:DeleteSelectFriendTag(buttonFunction)
        elseif k:Contains(buttonFunction, "Button_Notification_", false, false) == true then
            DealNotification(buttonFunction)
        elseif k:Contains(buttonFunction, "Button_InviteMatch_", false, false) == true then
            local gameInstance = LuaTestCaseInstance:GetCollisionWarGameInstance()
            if gameInstance.m_curLevelName == "NULL" then
                return
            end
            local chooseMapGameMode = LuaTestCaseInstance:GetChooseMapGameMode()
            local selectFriendNameList = slua.Array(stringType)
            for i, playerTag in pairs(chooseMapPlayerController.m_pSelectFriendMenu.m_pSelectPlayerTags) do
                selectFriendNameList:Add(playerTag.m_playerName)
            end
            if chooseMapPlayerController.m_pSelectFriendMenu.m_curMatchType == "twoTwoMatch" and selectFriendNameList:Num() == 1 then
                chooseMapGameMode:ReqFriendMatch(selectFriendNameList)
            elseif chooseMapPlayerController.m_pSelectFriendMenu.m_curMatchType == "threeThreeMatch" and selectFriendNameList:Num() == 2 then
                chooseMapGameMode:ReqFriendMatch(selectFriendNameList)
            end

            chooseMapGameMode.m_pSelectBattleMenu:StartUpClockCount()
        end
    end
end


function LuaInvisibleButtonClickCallback(buttonFunction, buttonLocation)
    local chooseMapPlayerController = LuaTestCaseInstance:GetChooseMapPlayerController()
    if buttonFunction == "Button_StoryMode" then
        print("SelectBattle::LuaInvisibleButtonClickCallback apply story mode")
        if chooseMapPlayerController:IsMapAvalibleForMatchType(0) == false then
            print("SelectBattle::LuaInvisibleButtonClickCallback does not contain such match type")
            return
        end
        local gameInstance = LuaTestCaseInstance:GetCollisionWarGameInstance()
        if gameInstance.m_curLevelName == "NULL" or gameInstance.m_accountStatus ~= "PreState" then
            return
        end
        local k = KismetStringLibrary()
        local levelName = k:Concat_StrStr(gameInstance.m_curLevelName, "_Roguelike")
        local g = GameplayStatics()
        g:OpenLevel(chooseMapPlayerController, levelName, true, "")
    elseif buttonFunction == "Button_SimpleMatch" then
        print("SelectBattle::LuaInvisibleButtonClickCallback apply simple match")
        if chooseMapPlayerController:IsMapAvalibleForMatchType(1) == false then
            print("SelectBattle::LuaInvisibleButtonClickCallback does not contain such match type")
            return
        end
        local chooseMapGameMode = LuaTestCaseInstance:GetChooseMapGameMode()
        local gameInstance = LuaTestCaseInstance:GetCollisionWarGameInstance()
        if gameInstance.m_curLevelName == "NULL" or gameInstance.m_accountStatus ~= "PreState" then
            return
        end
        chooseMapGameMode:ReqSimpleSingleMatch()
    elseif buttonFunction == "Button_SingleMatch" then
        if chooseMapPlayerController:IsMapAvalibleForMatchType(2) == false then
            return
        end
        local chooseMapGameMode = LuaTestCaseInstance:GetChooseMapGameMode()
        local gameInstance = LuaTestCaseInstance:GetCollisionWarGameInstance()
        if gameInstance.m_curLevelName == "NULL" or gameInstance.m_accountStatus ~= "PreState" then
            return
        end
        chooseMapGameMode:ReqSingleMatch()
    elseif buttonFunction == "Button_OneOnOne" then
        if chooseMapPlayerController:IsMapAvalibleForMatchType(3) == false then
            return
        end
        local chooseMapGameMode = LuaTestCaseInstance:GetChooseMapGameMode()
        local gameInstance = LuaTestCaseInstance:GetCollisionWarGameInstance()
        if gameInstance.m_curLevelName == "NULL" or gameInstance.m_accountStatus ~= "PreState" then
            return
        end
        chooseMapGameMode:ReqOneOneMatch()
    elseif buttonFunction == "Button_DoubleMatch" then
        if chooseMapPlayerController:IsMapAvalibleForMatchType(4) == false then
            return
        end
        chooseMapPlayerController:LoadSelectFriendMenu("twoTwoMatch")
    elseif buttonFunction == "Button_TrippleMatch" then
        if chooseMapPlayerController:IsMapAvalibleForMatchType(4) == false then
            return
        end
        chooseMapPlayerController:LoadSelectFriendMenu("threeThreeMatch")
    elseif buttonFunction == "Button_CancelMatch" then
        local chooseMapGameMode = LuaTestCaseInstance:GetChooseMapGameMode()
        chooseMapGameMode:ReqCancelMatch()
    elseif buttonFunction == "Button_BackToMainMenu" then
        local gameInstance = LuaTestCaseInstance:GetCollisionWarGameInstance()
        if gameInstance.m_accountStatus == "PreState" then
            chooseMapPlayerController.m_pSelectBattleMenu:AskFadeOut()
        end
    else
        if KismetStringLibrary:Contains(buttonFunction, "Friend_", false, false) == true then
            chooseMapPlayerController.m_pSelectBattleMenu.m_pChatBox:SwitchCustomFriend(buttonFunction)
        elseif KismetStringLibrary:Contains(buttonFunction, "Button_PlayerTag_", false, false) == true then
            chooseMapPlayerController.m_pSelectFriendMenu:SwitchPlayerInfo(buttonFunction)
        end
    end
end


function LuaMenuFadeOutDoneCallback(menuName)
    local chooseMapPlayerController = LuaTestCaseInstance:GetChooseMapPlayerController()
    if menuName == "SelectFriendMenu" then
        chooseMapPlayerController.m_pSelectFriendMenu:RemoveFromParent()
    elseif menuName == "NotificationMenu" then
        chooseMapPlayerController.m_pNotificationMenu:RemoveFromParent()
    elseif menuName == "SelectBattleMenu" then
        chooseMapPlayerController.m_pSelectBattleMenu:RemoveFromParent()
        local g = GameplayStatics()
        g:OpenLevel(chooseMapPlayerController, "MainMenuMap", true, "")
    end
end

function LuaNewNotification()
    local selectMapPlayerController = LuaTestCaseInstance:GetChooseMapPlayerController()
    local w = WidgetBlueprintFunctionLibrary()
    w:AddNotificationToSimpleMenu(selectMapPlayerController,
            selectMapPlayerController.m_pMainMenu.m_pMainMenuWidgetManager.m_BPNotificationClass,
            selectMapPlayerController.m_pMainMenu,"",50,0,0,0,0,0)
end

function LuaDealNewChatMessage(friendName, message)
    local selectMapPlayerController = LuaTestCaseInstance:GetChooseMapPlayerController()
    local w = WidgetBlueprintFunctionLibrary()
    w:AddMessageToChatBox(selectMapPlayerController, selectMapPlayerController.m_pSelectBattleMenu.m_pChatBox,
            friendName, message, 50)
end

function LuaDealNewMessage(message)
    if message == "matchSuccessful" then
        local selectMapPlayerController = LuaTestCaseInstance:GetChooseMapPlayerController()
        selectMapPlayerController:LoadEnsureEnterRoomMenu()
    elseif message == "PlayerEnterWorld" then
        local gameInstance = LuaTestCaseInstance:GetCollisionWarGameInstance()
        gameInstance.m_hasCSEnterWorld = true
    elseif message == "dispatchLevelModelList" then
        local selectMapGameMode = LuaTestCaseInstance:GetChooseMapGameMode()
        print("SelectBattle::LuaDealNewMessage recieve dispatchLevelModelList")
        selectMapGameMode.m_loadProgress = 50
        selectMapGameMode:SpawnLevelModel()
        local selectMapPlayerController = LuaTestCaseInstance:GetChooseMapPlayerController()
        selectMapPlayerController:SetLoadMenuProgressSliderPercentage(50)
    elseif message == "SpawnLevelModel" then
        local selectMapPlayerController = LuaTestCaseInstance:GetChooseMapPlayerController()
        local selectMapGameMode = LuaTestCaseInstance:GetChooseMapGameMode()
        selectMapGameMode.m_loadProgress = 100
        print("SelectBattle::LuaDealNewMessage recieve spawnLevelModel message now remove load menu")
        selectMapPlayerController.m_pLoadMenu:RemoveFromParent()
        selectMapPlayerController:LoadSelectMapMenu()
        local selectMapGameMode = LuaTestCaseInstance:GetChooseMapGameMode()
        selectMapGameMode:PlayFadeInLevelSequencePlayer("FadeIn")
        selectMapPlayerController:SetLoadMenuProgressSliderPercentage(100)
    elseif message == "Cancel match already" then
        local selectMapPlayerController = LuaTestCaseInstance:GetChooseMapPlayerController()
        selectMapPlayerController.m_pSelectBattleMenu:ResetMatchTimer()
    elseif message == "Player apply matching successfully" then
        local selectMapPlayerController = LuaTestCaseInstance:GetChooseMapPlayerController()
        selectMapPlayerController.m_pSelectBattleMenu:StartUpClockCount()
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
            g:OpenLevel(CWGameMode, "SelectBattleMap")
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