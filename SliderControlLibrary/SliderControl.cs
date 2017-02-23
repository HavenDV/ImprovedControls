using System;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Windows.Forms;

namespace T3000Controls
{
    public partial class SliderControl : UserControl
    {
        private MouseMover Mover { get; set; }

        public SliderControl()
        {
            InitializeComponent();

            Mover = new MouseMover(this);

            topHandle.Value = 33;
            backgroundControl.UpdateHandlePosition(topHandle);
            backgroundControl.TopZoneValue = topHandle.Value;

            bottomHandle.Value = 66;
            backgroundControl.UpdateHandlePosition(bottomHandle);
            backgroundControl.BottomZoneValue = bottomHandle.Value;
            backgroundControl.Refresh();
        }

        private void handle_MouseDown(object sender, MouseEventArgs e)
        {
            Mover.Start(e.Location, sender as Control);
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

            var point = Mover.GetPoint(e.Location);
            var handle = sender as HandleControl;
            if (handle == null)
            {
                return;
            }

            var value = backgroundControl.YToValue(point.Y + handle.Height / 2);
            var maxValue = Math.Max(backgroundControl.BottomValue, backgroundControl.TopValue);
            var minValue = Math.Min(backgroundControl.BottomValue, backgroundControl.TopValue);
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

            backgroundControl.TopZoneValue = topHandle.Value;
            backgroundControl.UpdateHandlePosition(topHandle);
            backgroundControl.Refresh();
        }

        private void bottomHandle_MouseMove(object sender, MouseEventArgs e)
        {
            if (!Mover.IsMoved)
            {
                return;
            }
            handle_MouseMove(sender, e);

            bottomHandle.Value = Math.Max(bottomHandle.Value, topHandle.Value);

            backgroundControl.BottomZoneValue = bottomHandle.Value;
            backgroundControl.UpdateHandlePosition(bottomHandle);
            backgroundControl.Refresh();
        }
    }
}
