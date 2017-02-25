namespace T3000Controls
{
    using System;
    using System.ComponentModel;
    using System.Windows.Forms;

    public partial class SliderControl : UserControl
    {
        #region DesignerProperties

        private float _topValue = 0;
        [Description("Top value"), Category("Data")]
        public float TopValue {
            get { return _topValue; }
            set {
                _topValue = value;

                if (DesignMode)
                {
                    Invalidate();
                }
            }
        }

        private float _bottomValue = 100;

        [Description("Bottom value"), Category("Data")]
        public float BottomValue
        {
            get { return _bottomValue; }
            set
            {
                _bottomValue = value;

                if (DesignMode)
                {
                    Invalidate();
                }
            }
        }

        private float _currentValue = 50;
        [Description("Current value"), Category("Data")]
        public float CurrentValue {
            get { return _currentValue; }
            set {
                _currentValue = value;

                if (DesignMode)
                {
                    Invalidate();
                }
            }
        }

        private bool _topZone = true;
        [Description("Top zone"), Category("Data")]
        public bool TopZone {
            get { return _topZone; }
            set {
                _topZone = value;
                topHandle.Visible = _topZone;

                if (DesignMode)
                {
                    Invalidate();
                }
            }
        }

        private bool _bottomZone = true;
        [Description("Bottom zone"), Category("Data")]
        public bool BottomZone {
            get { return _bottomZone; }
            set {
                _bottomZone = value;
                bottomHandle.Visible = _bottomZone;

                if (DesignMode)
                {
                    Invalidate();
                }
            }
        }

        private float _topZoneValue = 33;
        [Description("Top zone value"), Category("Data")]
        public float TopZoneValue {
            get { return _topZoneValue; }
            set {
                _topZoneValue = value;

                if (DesignMode)
                {
                    Invalidate();
                }
            }
        }

        private float _bottomZoneValue = 66;
        [Description("Bottom zone value"), Category("Data")]
        public float BottomZoneValue {
            get { return _bottomZoneValue; }
            set
            {
                _bottomZoneValue = value;

                if (DesignMode)
                {
                    Invalidate();
                }
            }
        }

        private float _stepValue = 10;
        [Description("Step value"), Category("Data")]
        public float StepValue {
            get { return _stepValue; }
            set {
                _stepValue = value;

                if (DesignMode)
                {
                    Invalidate();
                }
            }
        }

        #endregion

        public bool IsInverse => TopValue > BottomValue;

        private MouseMover Mover { get; set; }

        public SliderControl()
        {
            InitializeComponent();

            SetStyle(ControlStyles.ResizeRedraw, true);

            Mover = new MouseMover(this);
        }

        public float YToValue(float y)
        {
            return SliderUtilities.YToValue(y, TopValue, BottomValue, Height);
        }

        public float ValueToY(float value)
        {
            return SliderUtilities.ValueToY(value, TopValue, BottomValue, Height);
        }

        public float ValueToHeight(float value)
        {
            return IsInverse ? Height - ValueToY(value) : ValueToY(value);
        }

        public float GetOffsetForValue(float value)
        {
            return ValueToHeight(SliderUtilities.GetOffsetValueForValue(value, TopValue, BottomValue));
        }

        public void RefreshBackground()
        {
            //Update background control properties
            backgroundControl.TopZone = TopZone;
            backgroundControl.BottomZone = BottomZone;
            backgroundControl.TopZoneValueY = ValueToY(TopZoneValue);
            backgroundControl.BottomZoneValueY = ValueToY(BottomZoneValue);
            backgroundControl.CurrentValueY = ValueToY(CurrentValue);
            backgroundControl.StepHeight = ValueToHeight(StepValue);
            backgroundControl.BigOffsetY = GetOffsetForValue(StepValue);
            backgroundControl.SmallOffsetY = backgroundControl.BigOffsetY + ValueToHeight(StepValue/2);

            //Set top and bottom zone values from handles
            topHandle.Value = TopZoneValue;
            bottomHandle.Value = BottomZoneValue;

            //Update handles Y positions
            UpdateHandlePosition(topHandle);
            UpdateHandlePosition(bottomHandle);

            backgroundControl.Refresh();
        }

        public void UpdateHandlePosition(HandleControl handle)
        {
            var point = handle.Location;
            point.Y = (int)(ValueToY(handle.Value) - handle.Height / 2.0F);
            handle.Location = point;
        }

        private void handle_MouseDown(object sender, MouseEventArgs e)
        {
            Mover.Start(sender, e);
        }

        private void handle_MouseUp(object sender, MouseEventArgs e)
        {
            Mover.End();
        }

        private void handle_MouseMove(object sender, MouseEventArgs e)
        {
            if (!Mover.IsMoved)
            {
                return;
            }

            var handle = sender as HandleControl;
            if (handle == null)
            {
                return;
            }

            var point = Mover.GetPoint(e.Location);
            var value = YToValue(point.Y + handle.Height / 2.0F);
            var maxValue = Math.Max(BottomValue, TopValue);
            var minValue = Math.Min(BottomValue, TopValue);
            value = Math.Max(Math.Min(value, maxValue), minValue);

            handle.Value = value;
        }

        private void topHandle_MouseMove(object sender, MouseEventArgs e)
        {
            if (!Mover.IsMoved)
            {
                return;
            }
            handle_MouseMove(sender, e);

            topHandle.Value = IsInverse ?
                Math.Max(bottomHandle.Value, topHandle.Value) :
                Math.Min(bottomHandle.Value, topHandle.Value);
            TopZoneValue = topHandle.Value;
            RefreshBackground();
        }

        private void bottomHandle_MouseMove(object sender, MouseEventArgs e)
        {
            if (!Mover.IsMoved)
            {
                return;
            }
            handle_MouseMove(sender, e);

            bottomHandle.Value = IsInverse ?
                Math.Min(bottomHandle.Value, topHandle.Value) :
                Math.Max(bottomHandle.Value, topHandle.Value);
            BottomZoneValue = bottomHandle.Value;
            RefreshBackground();
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);

            RefreshBackground();
        }
    }
}
