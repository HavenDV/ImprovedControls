using System;
using System.ComponentModel;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Windows.Forms;

namespace T3000Controls
{
    public partial class SliderControl : UserControl
    {
        [Description("Top value"), Category("Data")]
        public float TopValue { get; set; } = 100;

        [Description("Bottom value"), Category("Data")]
        public float BottomValue { get; set; } = 0;

        [Description("Current value"), Category("Data")]
        public float CurrentValue { get; set; } = 50;

        [Description("Top zone"), Category("Data")]
        public bool TopZone { get; set; } = true;

        [Description("Bottom zone"), Category("Data")]
        public bool BottomZone { get; set; } = true;

        [Description("Top zone value"), Category("Data")]
        public float TopZoneValue { get; set; } = 66;

        [Description("Bottom zone value"), Category("Data")]
        public float BottomZoneValue { get; set; } = 33;

        public bool IsInverse => TopValue > BottomValue;

        private MouseMover Mover { get; set; }

        public SliderControl()
        {
            InitializeComponent();

            Mover = new MouseMover(this);

            topHandle.Value = TopZoneValue;
            bottomHandle.Value = BottomZoneValue;

            RefreshBackground();
        }

        public float YToValue(float y)
        {
            return Utilities.YToValue(y, TopValue, BottomValue, Height);
        }

        public float ValueToY(float value)
        {
            return Utilities.ValueToY(value, TopValue, BottomValue, Height);
        }

        public float GetOffsetForValue(int value)
        {
            return ValueToY(Utilities.GetOffsetValueForValue(value, TopValue, BottomValue));
        }

        public void RefreshBackground()
        {
            //Set top and bottom zone values from handles
            TopZoneValue = topHandle.Value;
            BottomZoneValue = bottomHandle.Value;

            //Update background control properties
            backgroundControl.TopZone = TopZone;
            backgroundControl.BottomZone = BottomZone;
            backgroundControl.TopZoneValueY = ValueToY(TopZoneValue);
            backgroundControl.BottomZoneValueY = ValueToY(BottomZoneValue);
            backgroundControl.CurrentValueY = ValueToY(CurrentValue);
            backgroundControl.StepHeight = ValueToY(10);
            backgroundControl.BigOffsetY = GetOffsetForValue(10);
            backgroundControl.SmallOffsetY = backgroundControl.BigOffsetY + ValueToY(5);

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

            topHandle.Value = Math.Min(bottomHandle.Value, topHandle.Value);
            RefreshBackground();
        }

        private void bottomHandle_MouseMove(object sender, MouseEventArgs e)
        {
            if (!Mover.IsMoved)
            {
                return;
            }
            handle_MouseMove(sender, e);

            bottomHandle.Value = Math.Max(bottomHandle.Value, topHandle.Value);
            RefreshBackground();
        }
    }
}
