Infinity.Scripting.CurrentScript:RegisterCallback("Infinity.OnScriptStart", function() 
    Inspector.Start()
    end)
Infinity.Scripting.CurrentScript:RegisterCallback("Infinity.OnScriptStop", function() 
    Inspector.Stop()
    end)
Infinity.Scripting.CurrentScript:RegisterCallback("Infinity.OnPulse", function()
    Inspector.OnPulse()
  end)
Infinity.Scripting.CurrentScript:RegisterCallback("Infinity.OnGUIDraw", function()
    Inspector.OnGuiDraw()
  end)
Infinity.Scripting.CurrentScript:RegisterCallback("Infinity.OnRenderD2D", function()
    Inspector.OnRenderD2D()
  end)

Infinity.Scripting.CurrentScript:RegisterCallback("Infinity.OnUIInteraction_KeyDown", Inspector.OnUIInteraction_KeyDown)