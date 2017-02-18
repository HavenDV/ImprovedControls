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
            this.panel1 = new T3000Controls.SliderControl();
            this.valueSlider = new T3000Controls.IndicatorControl();
            this.SuspendLayout();
            // 
            // panel1
            // 
            this.panel1.BackColor = System.Drawing.Color.Transparent;
            this.panel1.Location = new System.Drawing.Point(170, 37);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(101, 241);
            this.panel1.TabIndex = 2;
            // 
            // valueSlider
            // 
            this.valueSlider.BackColor = System.Drawing.Color.Transparent;
            this.valueSlider.Location = new System.Drawing.Point(0, 130);
            this.valueSlider.Name = "valueSlider";
            this.valueSlider.Size = new System.Drawing.Size(164, 55);
            this.valueSlider.SliderName = "Name";
            this.valueSlider.SliderValue = "Value";
            this.valueSlider.TabIndex = 1;
            this.valueSlider.MouseDown += new System.Windows.Forms.MouseEventHandler(this.slider1_MouseDown);
            this.valueSlider.MouseMove += new System.Windows.Forms.MouseEventHandler(this.slider1_MouseMove);
            this.valueSlider.MouseUp += new System.Windows.Forms.MouseEventHandler(this.slider1_MouseUp);
            // 
            // SliderControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Transparent;
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.valueSlider);
            this.Name = "SliderControl";
            this.Size = new System.Drawing.Size(412, 359);
            this.ResumeLayout(false);
        }

        #endregion

        private T3000Controls.IndicatorControl valueSlider;
        private SliderControl panel1;
    }
}
