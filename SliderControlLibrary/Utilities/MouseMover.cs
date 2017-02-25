﻿using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace T3000Controls
{
    public class MouseMover
    {
        public bool IsMoved { get; set; } = false;
        public Point Offset { get; set; }
        public Control Control { get; set; }
        public Control ParentControl { get; set; }

        public MouseMover(Control parentControl)
        {
            ParentControl = parentControl;
        }

        public void Start(Control control, Point location)
        {
            IsMoved = true;
            Offset = new Point(-location.X, -location.Y);
            Control = control;
        }

        public void Start(object sender, MouseEventArgs e)
        {
            Start(sender as Control, e.Location);
        }

        public void End()
        {
            IsMoved = false;
        }

        public Point GetPoint(Point location)
        {
            var point = ParentControl.PointToClient(Control.PointToScreen(location));
            point.Offset(Offset);

            return point;
        }
    }
}
