namespace T3000Controls
{
    using System;
    using System.Runtime.InteropServices;
    using System.Runtime.CompilerServices;
    using System.Runtime.InteropServices.ComTypes;
    using System.Threading;
    using System.Collections.Generic;
    using System.Collections;

    [ComVisible(false)]
    public delegate void ClickEventHandler();

    //[ComVisible(false)]
    //public delegate void DblClickEventHandler([In] bool Cancel);

    //[ComVisible(false)]
    //public delegate void ErrorEventHandler([In] short Number, [MarshalAs(UnmanagedType.BStr), In] string Description, [In] int SCode, [MarshalAs(UnmanagedType.BStr), In] string Source, [MarshalAs(UnmanagedType.BStr), In] string HelpFile, [In] int HelpContext, [In] bool CancelDisplay);

    [ComVisible(false)]
    public delegate void ValueChangedEventHandler([In] object sender, [In] float newValue);
    
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

    //[ComVisible(false)]
    [TypeLibType(TypeLibTypeFlags.FHidden)]
    [ClassInterface(ClassInterfaceType.None)]
    public sealed class ISliderControlEvents_SinkHelper : ISliderControlEvents
    {
        public int m_dwCookie;
        //public ClickEventHandler m_ClickDelegate;
        //public ErrorEventHandler m_ErrorDelegate;
        public ValueChangedEventHandler m_TopZoneValueChangedDelegate;
        public ValueChangedEventHandler m_BottomZoneValueChangedDelegate;
        public ValueChangedEventHandler m_CurrentValueChangedDelegate;
        public ValueChangedEventHandler m_TopValueChangedDelegate;
        public ValueChangedEventHandler m_BottomValueChangedDelegate;
        /*
        public void Click()
        {
            m_ClickDelegate?.Invoke();
        }
        public void Error([In] short obj0, [In] string obj1, [In] int obj2, [In] string obj3, [In] string obj4, [In] int obj5, [In] bool obj6)
        {
            m_ErrorDelegate?.Invoke(obj0, obj1, obj2, obj3, obj4, obj5, obj6);
        }
        */
        public void TopZoneValueChanged(object sender, float newValue)
        {
            m_TopZoneValueChangedDelegate?.Invoke(sender, newValue);
        }

        public void BottomZoneValueChanged(object sender, float newValue)
        {
            m_BottomZoneValueChangedDelegate?.Invoke(sender, newValue);
        }

        public void CurrentValueChanged(object sender, float newValue)
        {
            m_CurrentValueChangedDelegate?.Invoke(sender, newValue);
        }

        public void TopValueChanged(object sender, float newValue)
        {
            m_TopValueChangedDelegate?.Invoke(sender, newValue);
        }

        public void BottomValueChanged(object sender, float newValue)
        {
            m_BottomValueChangedDelegate?.Invoke(sender, newValue);
        }

    }

    internal sealed class ISliderControlEvents_EventProvider : ISliderControlEvents_Event, IDisposable
    {
        private IConnectionPointContainer m_ConnectionPointContainer;
        private ArrayList m_helpers;
        private IConnectionPoint m_ConnectionPoint;

        public ISliderControlEvents_EventProvider([In] object obj0)
        {
            this.m_ConnectionPointContainer = (IConnectionPointContainer)obj0;
        }

        private void Init()
        {
            var riid = new Guid("B2A56960-DA63-4936-A70D-86A00BFA1B0F");
            var ppCP = (IConnectionPoint)null;
            this.m_ConnectionPointContainer.FindConnectionPoint(ref riid, out ppCP);
            this.m_ConnectionPoint = ppCP;
            this.m_helpers = new ArrayList();
        }
        /*
        public event ClickEventHandler Click {
            add {
                Monitor.Enter((object)this);
                try
                {
                    if (this.m_ConnectionPoint == null)
                        this.Init();
                    var eventsSinkHelper = new ISliderControlEvents_SinkHelper();
                    int pdwCookie = 0;
                    this.m_ConnectionPoint.Advise((object)eventsSinkHelper, out pdwCookie);
                    eventsSinkHelper.m_dwCookie = pdwCookie;
                    eventsSinkHelper.m_ClickDelegate = value;
                    this.m_helpers.Add(eventsSinkHelper);
                }
                finally
                {
                    Monitor.Exit((object)this);
                }
            }
            remove {
                Monitor.Enter((object)this);
                try
                {
                    if (this.m_helpers == null)
                        return;
                    int count = this.m_helpers.Count;
                    int index = 0;
                    if (0 >= count)
                        return;
                    do
                    {
                        var aEventSinkHelper = (ISliderControlEvents_SinkHelper)m_helpers[index];
                        if (aEventSinkHelper.m_ClickDelegate != null && ((aEventSinkHelper.m_ClickDelegate.Equals((object)value) ? 1 : 0) & (int)byte.MaxValue) != 0)
                        {
                            m_helpers.RemoveAt(index);
                            m_ConnectionPoint.Unadvise(aEventSinkHelper.m_dwCookie);
                            if (count <= 1)
                            {
                                Marshal.ReleaseComObject(m_ConnectionPoint);
                                m_ConnectionPoint = null;
                                m_helpers = null;
                            }
                            return;
                        }
                        else
                            ++index;
                    }
                    while (index < count);
                }
                finally
                {
                    Monitor.Exit((object)this);
                }
            }
        }*/
        /*
        public event DblClickEventHandler DblClick {
            add
            {
                Monitor.Enter(this);
                try
                {
                    if (m_ConnectionPoint == null)
                        Init();

                    var helper = new ISliderControlEvents_SinkHelper();
                    int pdwCookie = 0;
                    m_ConnectionPoint.Advise(helper, out pdwCookie);

                    helper.m_dwCookie = pdwCookie;
                    helper.m_DblClickDelegate = value;

                    m_helpers.Add(helper);
                }
                finally
                {
                    Monitor.Exit(this);
                }
            }
            remove {
                Monitor.Enter(this);
                try
                {
                    if (m_helpers == null || m_helpers.Count == 0)
                        return;

                    for (int index = 0; index < m_helpers.Count; ++index)
                    {
                        var helper = m_helpers[index];
                        if (helper.m_DblClickDelegate != null && 
                            helper.m_DblClickDelegate.Equals(value))
                        {
                            m_helpers.RemoveAt(index);
                            m_ConnectionPoint.Unadvise(helper.m_dwCookie);
                            if (m_helpers.Count <= 1)
                            {
                                Marshal.ReleaseComObject(m_ConnectionPoint);
                                m_ConnectionPoint = null;
                                m_helpers = null;
                            }
                            return;
                        }
                    }
                }
                finally
                {
                    Monitor.Exit((object)this);
                }
            }
        }
        */
        public event ValueChangedEventHandler TopZoneValueChanged {
            add {
                Monitor.Enter(this);
                try
                {
                    if (m_ConnectionPoint == null)
                        Init();

                    var helper = new ISliderControlEvents_SinkHelper();
                    int pdwCookie = 0;
                    m_ConnectionPoint.Advise(helper, out pdwCookie);

                    helper.m_dwCookie = pdwCookie;
                    helper.m_TopZoneValueChangedDelegate = value;

                    m_helpers.Add(helper);
                }
                finally
                {
                    Monitor.Exit(this);
                }
            }
            remove {
                Monitor.Enter(this);
                try
                {
                    if (m_helpers == null || m_helpers.Count == 0)
                        return;

                    for (int index = 0; index < m_helpers.Count; ++index)
                    {
                        var helper = (ISliderControlEvents_SinkHelper)m_helpers[index];
                        if (helper.m_TopZoneValueChangedDelegate != null &&
                            helper.m_TopZoneValueChangedDelegate.Equals(value))
                        {
                            m_helpers.RemoveAt(index);
                            m_ConnectionPoint.Unadvise(helper.m_dwCookie);
                            if (m_helpers.Count <= 1)
                            {
                                Marshal.ReleaseComObject(m_ConnectionPoint);
                                m_ConnectionPoint = null;
                                m_helpers = null;
                            }
                            return;
                        }
                    }
                }
                finally
                {
                    Monitor.Exit((object)this);
                }
            }
        }


        public event ValueChangedEventHandler BottomZoneValueChanged {
            add {
                Monitor.Enter(this);
                try
                {
                    if (m_ConnectionPoint == null)
                        Init();

                    var helper = new ISliderControlEvents_SinkHelper();
                    int pdwCookie = 0;
                    m_ConnectionPoint.Advise(helper, out pdwCookie);

                    helper.m_dwCookie = pdwCookie;
                    helper.m_BottomZoneValueChangedDelegate = value;

                    m_helpers.Add(helper);
                }
                finally
                {
                    Monitor.Exit(this);
                }
            }
            remove {
                Monitor.Enter(this);
                try
                {
                    if (m_helpers == null || m_helpers.Count == 0)
                        return;

                    for (int index = 0; index < m_helpers.Count; ++index)
                    {
                        var helper = (ISliderControlEvents_SinkHelper)m_helpers[index];
                        if (helper.m_BottomZoneValueChangedDelegate != null &&
                            helper.m_BottomZoneValueChangedDelegate.Equals(value))
                        {
                            m_helpers.RemoveAt(index);
                            m_ConnectionPoint.Unadvise(helper.m_dwCookie);
                            if (m_helpers.Count <= 1)
                            {
                                Marshal.ReleaseComObject(m_ConnectionPoint);
                                m_ConnectionPoint = null;
                                m_helpers = null;
                            }
                            return;
                        }
                    }
                }
                finally
                {
                    Monitor.Exit((object)this);
                }
            }
        }
        /*
        public event ErrorEventHandler Error {
            add {
                Monitor.Enter((object)this);
                try
                {
                    if (this.m_ConnectionPoint == null)
                        this.Init();
                    var eventsSinkHelper = new ISliderControlEvents_SinkHelper();
                    int pdwCookie = 0;
                    this.m_ConnectionPoint.Advise((object)eventsSinkHelper, out pdwCookie);
                    eventsSinkHelper.m_dwCookie = pdwCookie;
                    eventsSinkHelper.m_ErrorDelegate = value;
                    this.m_helpers.Add(eventsSinkHelper);
                }
                finally
                {
                    Monitor.Exit((object)this);
                }
            }
            remove {
                Monitor.Enter((object)this);
                try
                {
                    if (this.m_helpers == null)
                        return;
                    int count = this.m_helpers.Count;
                    int index = 0;
                    if (0 >= count)
                        return;
                    do
                    {
                        var aEventSinkHelper = (ISliderControlEvents_SinkHelper)this.m_helpers[index];
                        if (aEventSinkHelper.m_ErrorDelegate != null && ((aEventSinkHelper.m_ErrorDelegate.Equals((object)value) ? 1 : 0) & (int)byte.MaxValue) != 0)
                        {
                            this.m_helpers.RemoveAt(index);
                            this.m_ConnectionPoint.Unadvise(aEventSinkHelper.m_dwCookie);
                            if (count <= 1)
                            {
                                Marshal.ReleaseComObject((object)this.m_ConnectionPoint);
                                this.m_ConnectionPoint = (IConnectionPoint)null;
                                this.m_helpers = null;
                            }
                            return;
                        }
                        else
                            ++index;
                    }
                    while (index < count);
                }
                finally
                {
                    Monitor.Exit((object)this);
                }
            }
        }
        */
        ~ISliderControlEvents_EventProvider()
        {
            Monitor.Enter((object)this);
            try
            {
                if (this.m_ConnectionPoint == null)
                    return;
                int count = this.m_helpers.Count;
                int index = 0;
                if (0 < count)
                {
                    do
                    {
                        var helper = (ISliderControlEvents_SinkHelper) m_helpers[index];
                        m_ConnectionPoint.Unadvise(helper.m_dwCookie);
                        ++index;
                    }
                    while (index < count);
                }
                Marshal.ReleaseComObject((object)this.m_ConnectionPoint);
            }
            catch (Exception)
            {
            }
            finally
            {
                Monitor.Exit((object)this);
            }
        }

        public void Dispose()
        {
            GC.SuppressFinalize((object)this);
        }
    }

    //[TypeLibType(TypeLibTypeFlags.FHidden)]
    //[ComVisible(false)]
    [ComEventInterface(typeof(ISliderControlEvents), typeof(ISliderControlEvents_EventProvider))]
    internal interface ISliderControlEvents_Event
    {
        //event ClickEventHandler Click;
        //event DblClickEventHandler DblClick;
        //event ErrorEventHandler Error;
        event ValueChangedEventHandler TopZoneValueChanged;
        event ValueChangedEventHandler BottomZoneValueChanged;
    }
}
