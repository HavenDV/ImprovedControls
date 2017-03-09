namespace T3000Controls
{
    using System;
    using System.Runtime.InteropServices;

    //[ComVisible(false)]
    //public delegate void ClickEventHandler();

    //[ComVisible(false)]
    //public delegate void ErrorEventHandler([In] short Number, [MarshalAs(UnmanagedType.BStr), In] string Description, [In] int SCode, [MarshalAs(UnmanagedType.BStr), In] string Source, [MarshalAs(UnmanagedType.BStr), In] string HelpFile, [In] int HelpContext, [In] bool CancelDisplay);

    [ComVisible(false)]
    public delegate void ValueChangedEventHandler(object sender, float newValue);
    
    [Guid("B2A56960-DA63-4936-A70D-86A00BFA1B0F")]
    [InterfaceType(ComInterfaceType.InterfaceIsIDispatch)]
    public interface ISliderControlEvents
    {
        [DispId(1)]
        void TopZoneValueChanged(object sender, float newValue);

        [DispId(2)]
        void BottomZoneValueChanged(object sender, float newValue);

        [DispId(3)]
        void CurrentValueChanged(object sender, float newValue);

        [DispId(4)]
        void TopValueChanged(object sender, float newValue);

        [DispId(5)]
        void BottomValueChanged(object sender, float newValue);

        //[DispId(-608)]
        //[MethodImpl(MethodImplOptions.PreserveSig | MethodImplOptions.InternalCall, MethodCodeType = MethodCodeType.Runtime)]
        //void Error([In] short Number, [MarshalAs(UnmanagedType.BStr), In] string Description, [In] int SCode, [MarshalAs(UnmanagedType.BStr), In] string Source, [MarshalAs(UnmanagedType.BStr), In] string HelpFile, [In] int HelpContext, [In] bool CancelDisplay);
    }
}
