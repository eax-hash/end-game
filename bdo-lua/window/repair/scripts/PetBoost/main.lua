Infinity.Scripting.CurrentScript:RegisterCallback("Infinity.OnScriptStart", function() 
    PetBoost.Start()
    end)
Infinity.Scripting.CurrentScript:RegisterCallback("Infinity.OnScriptStop", function() 
    PetBoost.Stop()
    end)
Infinity.Scripting.CurrentScript:RegisterCallback("Infinity.OnPulse", function() 
    PetBoost.OnPulse()
    end)
Infinity.Scripting.CurrentScript:RegisterCallback("Infinity.OnGUIDraw", function()
    PetBoost.OnGuiDraw()
  end)
Infinity.Scripting.CurrentScript:RegisterCallback("Infinity.OnRenderD2D", function()
    PetBoost.OnRenderD2D()
  end)

Infinity.Scripting.CurrentScript:RegisterCallback("Infinity.OnPacketReceive", PetBoost.OnPacketReceive)