---
--- Generated by EmmyLua(https://github.com/EmmyLua)
--- Created by Administrator.
--- DateTime: 2019/1/4 10:22
---

local LuaTestCase=import('LuaTestCase');
local LuaTestCaseInstance = LuaTestCase();

EffectScoreCountFunction = {}

function EffectKouXueScoreCount(pEffect, pCharacter)
    print("EffectScoreCountFunction.EffectKouXueScoreCount on")
    if LuaTestCaseInstance:IsObjectValid(pEffect) == false or
            LuaTestCaseInstance:IsObjectValid(pEffect.m_pOriginGeo) == false or
            LuaTestCaseInstance:IsObjectValid(pCharacter) == false or
            LuaTestCaseInstance:IsObjectValid(pEffect.m_pHost) == false then
        return
    end
    if pCharacter.m_Hp <= 0 then
        local physCalculator = LuaTestCaseInstance:GetPhysCalculator()
        local killScorePair = FScorePair("killEnermy", pCharacter, 1)
        physCalculator.m_tempScorePairs:Add(killScorePair)
        local outputScorePair = FScorePair("outputScore", pCharacter, 0)
        physCalculator.m_tempScorePairs:Add(outputScorePair)
    end
end

function EffectScoreCountFunction.LuaDealEffectScoreCountFunction(pEffect, pCharacter)
    print("EffectScoreCountFunction.LuaDealEffectScoreCountFunction on")
    if pEffect.m_effectName == "Effect_KouXue" then
        EffectKouXueScoreCount(pEffect, pCharacter)
    end
end

return EffectScoreCountFunction