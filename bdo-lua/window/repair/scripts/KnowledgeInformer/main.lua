Infinity.Scripting.CurrentScript:RegisterCallback("Infinity.OnScriptStart", function() 
    KnowledgeInformer.Start()
    end)
Infinity.Scripting.CurrentScript:RegisterCallback("Infinity.OnScriptStop", function() 
    KnowledgeInformer.Stop()
    end)
Infinity.Scripting.CurrentScript:RegisterCallback("Infinity.OnPulse", function()
    KnowledgeInformer.OnPulse()
  end)
Infinity.Scripting.CurrentScript:RegisterCallback("Infinity.OnGUIDraw", function()
    KnowledgeInformer.OnGuiDraw()
  end)
Infinity.Scripting.CurrentScript:RegisterCallback("Infinity.OnRenderD2D", function()
    KnowledgeInformer.OnRenderD2D()
  end)