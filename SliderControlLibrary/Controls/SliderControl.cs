namespace T3000Controls
{
    using System;
    using System.ComponentModel;
    using System.Windows.Forms;
    using System.Runtime.InteropServices;
    using System.Drawing;

    public partial class SliderControl : UserControl
    {
        #region DesignerProperties

        private float _topValue = 0;
        [Description("Top value"), Category("Data")]
        public float TopValue {
            get { return _topValue; }
            set
            {
                _topValue = value;
                Invalidate();
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
                Invalidate();
            }
        }

        private float _currentValue = 50;
        [Description("Current value"), Category("Data")]
        public float CurrentValue {
            get { return _currentValue; }
            set 
            {
                _currentValue = value;
                Invalidate();
            }
        }

        [Description("Top zone"), Category("Data")]
        public bool TopZone
        {
            get { return backgroundControl.TopZone; }
            set
            {
                backgroundControl.TopZone = value;
                topHandle.Visible = value;
            }
        }

        [Description("Bottom zone"), Category("Data")]
        public bool BottomZone
        {
            get { return backgroundControl.BottomZone; }
            set
            {
                backgroundControl.BottomZone = value;
                bottomHandle.Visible = value;
            }
        }

        private float _topZoneValue = 33;
        [Description("Top zone value"), Category("Data")]
        public float TopZoneValue {
            get { return _topZoneValue; }
            set
            {
                _topZoneValue = value;
                Invalidate();
            }
        }

        private float _bottomZoneValue = 66;
        [Description("Bottom zone value"), Category("Data")]
        public float BottomZoneValue {
            get { return _bottomZoneValue; }
            set
            {
                _bottomZoneValue = value;
                 Invalidate();
            }
        }

        private float _stepValue = 10;
        [Description("Step value"), Category("Data")]
        public float StepValue {
            get { return _stepValue; }
            set
            {
                _stepValue = value;
                Invalidate();
            }
        }

        private bool _twoHandleControl = true;
        [Description("Two handle control"), Category("Appearance")]
        public bool TwoHandleControl {
            get { return _twoHandleControl; }
            set
            {
                _twoHandleControl = value;
                middleHandle.Visible = !value;

                Invalidate();
            }
        }

        private string _handlesAdditionalText = " F";
        [Description("Two handle control"), Category("Appearance")]
        public string HandlesAdditionalText {
            get { return _handlesAdditionalText; }
            set {
                _handlesAdditionalText = value;
                topHandle.AdditionalText = value;
                middleHandle.AdditionalText = value;
                bottomHandle.AdditionalText = value;

                Invalidate();
            }
        }

        [Description("Color for lines"), Category("Appearance")]
        public Color LinesColorColor {
            get { return backgroundControl.LinesColor; }
            set { backgroundControl.LinesColor = value; }
        }

        [Description("Color for borders"), Category("Appearance")]
        public Color BorderColor {
            get { return backgroundControl.BorderColor; }
            set { backgroundControl.BorderColor = value; }
        }

        [Description("Color for top zone"), Category("Appearance")]
        public Color TopZoneColor {
            get { return backgroundControl.TopZoneColor; }
            set { backgroundControl.TopZoneColor = value; }
        }

        [Description("Color for bottom zone"), Category("Appearance")]
        public Color BottomZoneColor {
            get { return backgroundControl.BottomZoneColor; }
            set { backgroundControl.BottomZoneColor = value; }
        }

        [Description("Color for current value"), Category("Appearance")]
        public Color CurrentValueColor {
            get { return backgroundControl.CurrentValueColor; }
            set { backgroundControl.CurrentValueColor = value; }
        }

        [Description("Width for background panel"), Category("Appearance")]
        public int BackgroundWidth {
            get { return backgroundControl.Width; }
            set
            {
                backgroundControl.Width = value;
                topHandle.HandleWidth = value;
                middleHandle.HandleWidth = value;
                bottomHandle.HandleWidth = value;

                Invalidate();
            }
        }

        [Description("Height for handles"), Category("Appearance")]
        public int HandlesHeight {
            get { return topHandle.HandleHeight; }
            set
            {
                topHandle.HandleHeight = value;
                middleHandle.HandleHeight = value;
                bottomHandle.HandleHeight = value;

                Invalidate();
            }
        }

        #endregion

        private MouseMover Mover { get; }

        public SliderControl()
        {
            InitializeComponent();

            ResizeRedraw = true;
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
            return SliderUtilities.ValueToHeight(value, TopValue, BottomValue, Height);
        }

        public float GetOffsetForValue(float value)
        {
            return SliderUtilities.GetOffsetForValue(value, TopValue, BottomValue, Height);
        }

        public void UpdateHandlePositionFromValue(HandleControl handle)
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

            var point = Mover.GetPoint(e);
            var value = YToValue(point.Y + handle.Height / 2.0F);

            //Restricts value from top and bottom values
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

            //Restricts value from bottom handle value
            topHandle.Value = TopValue > BottomValue ?
                Math.Max(bottomHandle.Value, topHandle.Value) :
                Math.Min(bottomHandle.Value, topHandle.Value);

            TopZoneValue = topHandle.Value;
            Refresh();
        }

        private void bottomHandle_MouseMove(object sender, MouseEventArgs e)
        {
            if (!Mover.IsMoved)
            {
                return;
            }
            handle_MouseMove(sender, e);

            //Restricts value from top handle value
            bottomHandle.Value = TopValue > BottomValue ?
                Math.Min(bottomHandle.Value, topHandle.Value) :
                Math.Max(bottomHandle.Value, topHandle.Value);

            BottomZoneValue = bottomHandle.Value;
            Refresh();
        }

        private void middleHandle_MouseMove(object sender, MouseEventArgs e)
        {
            if (TwoHandleControl || !Mover.IsMoved)
            {
                return;
            }
            var prevValue = middleHandle.Value;
            handle_MouseMove(sender, e);
            var delta = middleHandle.Value - prevValue;

            bottomHandle.Value += delta;
            topHandle.Value += delta;

            TopZoneValue = topHandle.Value;
            BottomZoneValue = bottomHandle.Value;

            Refresh();
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);

            //Update background control properties
            backgroundControl.TopZoneValueY = ValueToY(TopZoneValue);
            backgroundControl.BottomZoneValueY = ValueToY(BottomZoneValue);
            backgroundControl.CurrentValueY = ValueToY(CurrentValue);
            backgroundControl.StepHeight = ValueToHeight(StepValue);
            backgroundControl.BigOffsetY = GetOffsetForValue(StepValue);
            backgroundControl.SmallOffsetY = backgroundControl.BigOffsetY + ValueToHeight(StepValue / 2);

            //Set top and bottom zone values from handles
            topHandle.Value = TopZoneValue;
            bottomHandle.Value = BottomZoneValue;
            middleHandle.Value = (TopZoneValue + BottomZoneValue)/2;

            //Update handles Y positions
            UpdateHandlePositionFromValue(topHandle);
            UpdateHandlePositionFromValue(bottomHandle);
            UpdateHandlePositionFromValue(middleHandle);

            backgroundControl.Refresh();

            using (var brush = new SolidBrush(Color.Red))
            {
                var point = new PointF(backgroundControl.Right, backgroundControl.Top);
                e.Graphics.DrawString(TopValue.ToString("F1"), DefaultFont, brush, point);
                point.Y = backgroundControl.Bottom - DefaultFont.GetHeight(e.Graphics);
                e.Graphics.DrawString(BottomValue.ToString("F1"), DefaultFont, brush, point);
            }
        }

        [ComRegisterFunction()]
        public static void RegisterClass(string key) => ComUtilities.RegisterControlClass(key);

        [ComUnregisterFunction()]
        public static void UnregisterClass(string key) => ComUtilities.UnregisterControlClass(key);
    }
}
