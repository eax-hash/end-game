Infinity.Scripting.CurrentScript:RegisterCallback("Infinity.OnScriptStart", function() 
    MailRemover.Start()
    end)
Infinity.Scripting.CurrentScript:RegisterCallback("Infinity.OnScriptStop", function() 
    MailRemover.Stop()
    end)
Infinity.Scripting.CurrentScript:RegisterCallback("Infinity.OnPulse", function()
    MailRemover.OnPulse()
  end)
Infinity.Scripting.CurrentScript:RegisterCallback("Infinity.OnGUIDraw", function()
    MailRemover.OnGuiDraw()
  end)
Infinity.Scripting.CurrentScript:RegisterCallback("Infinity.OnRenderD2D", function()
    MailRemover.OnRenderD2D()
  end)