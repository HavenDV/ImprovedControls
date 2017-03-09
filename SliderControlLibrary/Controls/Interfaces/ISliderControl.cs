namespace T3000Controls
{
    using System;
    using System.Drawing;
    using System.Runtime.InteropServices;

    //[Guid("02D50671-77C4-411A-B6F4-1C29C44814CC")]
    //[InterfaceType(ComInterfaceType.InterfaceIsDual)]
    public interface ISliderControl
    {
        float TopValue { get; set; }
        float BottomValue { get; set; }
        float CurrentValue { get; set; }
        bool TopZone { get; set; }
        bool BottomZone { get; set; }
        float TopZoneValue { get; set; }
        float BottomZoneValue { get; set; }
        float StepValue { get; set; }
        bool TwoSliderMode { get; set; }
        string AdditionalText { get; set; }
        Color LinesColor { get; set; }
        Color BorderColor { get; set; }
        Color TopZoneColor { get; set; }
        Color BottomZoneColor { get; set; }
        Color CurrentValueColor { get; set; }
        int BackgroundWidth { get; set; }
        int HandlesHeight { get; set; }
        Color HandlesBorderColor { get; set; }
        Color MiddleHandleColor { get; set; }
        Color IndicatorColor { get; set; }
        Color IndicatorBorderColor { get; set; }
        Size IndicatorSize { get; set; }
        bool EnableIndicator { get; set; }
        bool IsSimpleIndicator { get; set; }
        string IndicatorText { get; set; }
    }
}