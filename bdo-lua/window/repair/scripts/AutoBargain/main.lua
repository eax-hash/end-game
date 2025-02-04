Infinity.Scripting.CurrentScript:RegisterCallback("Infinity.OnScriptStart", function() 
    AutoBargain.Start()
    end)
Infinity.Scripting.CurrentScript:RegisterCallback("Infinity.OnScriptStop", function() 
    AutoBargain.Stop()
    end)
Infinity.Scripting.CurrentScript:RegisterCallback("Infinity.OnPulse", function()
    AutoBargain.OnPulse()
  end)
Infinity.Scripting.CurrentScript:RegisterCallback("Infinity.OnGUIDraw", function()
    AutoBargain.OnGuiDraw()
  end)
Infinity.Scripting.CurrentScript:RegisterCallback("Infinity.OnRenderD2D", function()
    AutoBargain.OnRenderD2D()
  end)

Infinity.Scripting.CurrentScript:RegisterGlobalHook("FromClient_DialogFunctionClick_Contents_Shop", AutoBargain.On_FromClient_DialogFunctionClick_Contents_Shop)
Infinity.Scripting.CurrentScript:RegisterGlobalHook("FromClient_MarketItemList_All_UpdateItemList", AutoBargain.On_FromClient_MarketItemList_All_UpdateItemList)
Infinity.Scripting.CurrentScript:RegisterGlobalHook("FromClient_TradeGameStart", AutoBargain.On_FromClient_TradeGameStart)
Infinity.Scripting.CurrentScript:RegisterGlobalHook("FromClient_TradeGameResult", AutoBargain.On_FromClient_TradeGameResult)
Infinity.Scripting.CurrentScript:RegisterGlobalHook("FromClient_TradeGameReciveDice", AutoBargain.On_FromClient_TradeGameReciveDice)
