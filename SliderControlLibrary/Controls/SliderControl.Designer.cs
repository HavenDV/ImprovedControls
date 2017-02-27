namespace T3000Controls
{
    partial class SliderControl
    {
        /// <summary> 
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.middleHandle = new T3000Controls.HandleControl();
            this.bottomHandle = new T3000Controls.HandleControl();
            this.topHandle = new T3000Controls.HandleControl();
            this.backgroundControl = new T3000Controls.BackgroundControl();
            this.SuspendLayout();
            // 
            // middleHandle
            // 
            this.middleHandle.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.middleHandle.BackColor = System.Drawing.Color.GreenYellow;
            this.middleHandle.BorderColor = System.Drawing.Color.White;
            this.middleHandle.HandleHeight = 10;
            this.middleHandle.HandleWidth = 50;
            this.middleHandle.Location = new System.Drawing.Point(0, 42);
            this.middleHandle.Name = "middleHandle";
            this.middleHandle.Size = new System.Drawing.Size(100, 16);
            this.middleHandle.TabIndex = 4;
            this.middleHandle.Value = 50F;
            this.middleHandle.MouseDown += new System.Windows.Forms.MouseEventHandler(this.handle_MouseDown);
            this.middleHandle.MouseMove += new System.Windows.Forms.MouseEventHandler(this.middleHandle_MouseMove);
            this.middleHandle.MouseUp += new System.Windows.Forms.MouseEventHandler(this.handle_MouseUp);
            // 
            // bottomHandle
            // 
            this.bottomHandle.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.bottomHandle.BackColor = System.Drawing.Color.Red;
            this.bottomHandle.BorderColor = System.Drawing.Color.White;
            this.bottomHandle.HandleHeight = 10;
            this.bottomHandle.HandleWidth = 50;
            this.bottomHandle.Location = new System.Drawing.Point(0, 58);
            this.bottomHandle.Name = "bottomHandle";
            this.bottomHandle.Size = new System.Drawing.Size(100, 16);
            this.bottomHandle.TabIndex = 1;
            this.bottomHandle.Value = 66F;
            this.bottomHandle.MouseDown += new System.Windows.Forms.MouseEventHandler(this.handle_MouseDown);
            this.bottomHandle.MouseMove += new System.Windows.Forms.MouseEventHandler(this.bottomHandle_MouseMove);
            this.bottomHandle.MouseUp += new System.Windows.Forms.MouseEventHandler(this.handle_MouseUp);
            // 
            // topHandle
            // 
            this.topHandle.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.topHandle.BackColor = System.Drawing.Color.DeepSkyBlue;
            this.topHandle.BorderColor = System.Drawing.Color.White;
            this.topHandle.HandleHeight = 10;
            this.topHandle.HandleWidth = 50;
            this.topHandle.Location = new System.Drawing.Point(0, 25);
            this.topHandle.Name = "topHandle";
            this.topHandle.Size = new System.Drawing.Size(100, 16);
            this.topHandle.TabIndex = 3;
            this.topHandle.Value = 33F;
            this.topHandle.MouseDown += new System.Windows.Forms.MouseEventHandler(this.handle_MouseDown);
            this.topHandle.MouseMove += new System.Windows.Forms.MouseEventHandler(this.topHandle_MouseMove);
            this.topHandle.MouseUp += new System.Windows.Forms.MouseEventHandler(this.handle_MouseUp);
            // 
            // backgroundControl
            // 
            this.backgroundControl.BackColor = System.Drawing.Color.GreenYellow;
            this.backgroundControl.BigOffsetY = 10F;
            this.backgroundControl.BorderColor = System.Drawing.Color.Black;
            this.backgroundControl.BottomZone = true;
            this.backgroundControl.BottomZoneColor = System.Drawing.Color.Red;
            this.backgroundControl.BottomZoneValueY = 66F;
            this.backgroundControl.CurrentValueY = 50F;
            this.backgroundControl.Dock = System.Windows.Forms.DockStyle.Left;
            this.backgroundControl.LinesColor = System.Drawing.Color.LightGray;
            this.backgroundControl.Location = new System.Drawing.Point(0, 0);
            this.backgroundControl.Name = "backgroundControl";
            this.backgroundControl.Size = new System.Drawing.Size(49, 100);
            this.backgroundControl.SmallOffsetY = 5F;
            this.backgroundControl.StepHeight = 10F;
            this.backgroundControl.TabIndex = 2;
            this.backgroundControl.TopZone = true;
            this.backgroundControl.TopZoneColor = System.Drawing.Color.DeepSkyBlue;
            this.backgroundControl.TopZoneValueY = 33F;
            // 
            // SliderControl
            // 
            this.BackColor = System.Drawing.Color.Transparent;
            this.Controls.Add(this.middleHandle);
            this.Controls.Add(this.bottomHandle);
            this.Controls.Add(this.topHandle);
            this.Controls.Add(this.backgroundControl);
            this.Name = "SliderControl";
            this.Size = new System.Drawing.Size(100, 100);
            this.ResumeLayout(false);

        }

        #endregion

        private HandleControl topHandle;
        private HandleControl bottomHandle;
        private BackgroundControl backgroundControl;
        private HandleControl middleHandle;
    }
}
