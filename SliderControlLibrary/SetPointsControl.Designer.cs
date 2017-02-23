namespace T3000Controls
{
    partial class SetPointsControl
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
            this.panel = new T3000Controls.SliderControl();
            this.valueSlider = new T3000Controls.IndicatorControl();
            this.SuspendLayout();
            // 
            // panel
            // 
            this.panel.BackColor = System.Drawing.Color.Transparent;
            this.panel.Location = new System.Drawing.Point(170, 37);
            this.panel.Name = "panel";
            this.panel.Size = new System.Drawing.Size(102, 206);
            this.panel.TabIndex = 2;
            // 
            // valueSlider
            // 
            this.valueSlider.BackColor = System.Drawing.Color.Transparent;
            this.valueSlider.Location = new System.Drawing.Point(0, 113);
            this.valueSlider.Name = "valueSlider";
            this.valueSlider.Size = new System.Drawing.Size(164, 55);
            this.valueSlider.SliderName = "Name";
            this.valueSlider.SliderValue = "Value";
            this.valueSlider.TabIndex = 1;
            this.valueSlider.MouseDown += new System.Windows.Forms.MouseEventHandler(this.slider1_MouseDown);
            this.valueSlider.MouseMove += new System.Windows.Forms.MouseEventHandler(this.slider1_MouseMove);
            this.valueSlider.MouseUp += new System.Windows.Forms.MouseEventHandler(this.slider1_MouseUp);
            // 
            // SetPointsControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Transparent;
            this.Controls.Add(this.panel);
            this.Controls.Add(this.valueSlider);
            this.Name = "SetPointsControl";
            this.Size = new System.Drawing.Size(412, 359);
            this.ResumeLayout(false);

        }

        #endregion

        private T3000Controls.IndicatorControl valueSlider;
        private SliderControl panel;
    }
}
