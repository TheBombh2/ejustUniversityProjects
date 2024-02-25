using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace LAB
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        string option;
        List<int>  numsTBA = new List<int>();
        int final = 0;

        
        private void num1Btn_Click(object sender, EventArgs e)
        {
            calcTextBox.Text = calcTextBox.Text + num1Btn.Text;
        }

        private void num2Btn_Click(object sender, EventArgs e)
        {
            calcTextBox.Text = calcTextBox.Text + num2Btn.Text;
        }

        private void num3Btn_Click(object sender, EventArgs e)
        {
            calcTextBox.Text = calcTextBox.Text + num3Btn.Text;
        }

        private void num4Btn_Click(object sender, EventArgs e)
        {
            calcTextBox.Text = calcTextBox.Text + num4Btn.Text;
        }

        private void num5Btn_Click(object sender, EventArgs e)
        {
            calcTextBox.Text = calcTextBox.Text + num5Btn.Text;
        }

        private void num6Btn_Click(object sender, EventArgs e)
        {
            calcTextBox.Text = calcTextBox.Text + num6Btn.Text;
        }

        private void num7Btn_Click(object sender, EventArgs e)
        {
            calcTextBox.Text = calcTextBox.Text + num7Btn.Text;
        }

        private void num8Btn_Click(object sender, EventArgs e)
        {
            calcTextBox.Text = calcTextBox.Text + num8Btn.Text;
        }

        private void num9Btn_Click(object sender, EventArgs e)
        {
            calcTextBox.Text = calcTextBox.Text + num9Btn.Text;
        }

        private void num0Btn_Click(object sender, EventArgs e)
        {
            calcTextBox.Text = calcTextBox.Text + num0Btn.Text;
        }

        private void CLRBtn_Click(object sender, EventArgs e)
        {
            calcTextBox.Text = "";
            final = 0;
            numsTBA.Clear();
        }

        private void MINUSBtn_Click(object sender, EventArgs e)
        {
            option = "-";
            try
            {
                numsTBA.Add(int.Parse(calcTextBox.Text));
            }
            catch
            {
                MessageBox.Show("Error in input");
            }

            calcTextBox.Clear();
        }
        private void btnADD_Click(object sender, EventArgs e)
        {
            option = "+";
            try
            {
                numsTBA.Add(int.Parse(calcTextBox.Text));
            }
            catch
            {
                MessageBox.Show("Error in input");
            }

            calcTextBox.Clear();
            
        }

        

        private void btnMult_Click(object sender, EventArgs e)
        {
            option = "*";
            try
            {
                numsTBA.Add(int.Parse(calcTextBox.Text));
            }
            catch
            {
                MessageBox.Show("Error in input");
            }

            calcTextBox.Clear();
        }

        private void btnDivide_Click(object sender, EventArgs e)
        {
            option = "/";
            try
            {
                numsTBA.Add(int.Parse(calcTextBox.Text));
            }
            catch
            {
                MessageBox.Show("Error in input");
            }

            calcTextBox.Clear();
        }

        private void EQLBtn_Click(object sender, EventArgs e)
        {
            switch (option)
            {
                case "+":
                    foreach (int i in numsTBA)
                    {
                        final += i;

                    }
                    try
                    {
                        final += int.Parse(calcTextBox.Text);
                    }
                    catch
                    {
                        MessageBox.Show("Error in Input");
                        calcTextBox.Clear();
                        final = 0;
                        numsTBA.Clear();
                    }
                    calcTextBox.Text = final.ToString();
                    final = 0;
                    numsTBA.Clear();
                    break;
                    
                case "-":

                    for (int i = 0; i < numsTBA.Count; i++)
                    {
                        if (i == 0)
                        {
                            final = numsTBA[i];
                            continue;
                        }
                        final -= numsTBA[i];

                    }

                    try
                    {
                        final -= int.Parse(calcTextBox.Text);
                    }
                    catch
                    {
                        MessageBox.Show("Error in Input");
                        calcTextBox.Clear();
                        final = 0;
                        numsTBA.Clear();
                    }

                    calcTextBox.Text = final.ToString();
                    final = 0;
                    numsTBA.Clear();
                    break;

                 case "*":
                    for (int i = 0; i < numsTBA.Count; i++)
                    {
                        if (i == 0)
                        {
                            final = numsTBA[i];
                            continue;
                        }
                        final *= numsTBA[i];

                    }
                    try
                    {
                        final *= int.Parse(calcTextBox.Text);
                    }
                    catch
                    {
                        MessageBox.Show("Error in Input");
                        calcTextBox.Clear();
                        final = 0;
                        numsTBA.Clear();
                    }
                    calcTextBox.Clear();
                    final = 0;
                    numsTBA.Clear();
                    break;

                 case "/":
                    for (int i = 0; i < numsTBA.Count; i++)
                    {
                        if (i == 0)
                        {
                            final = numsTBA[i];
                            continue;
                        }
                        final /= numsTBA[i];

                    }
                    try
                    {
                        final /= int.Parse(calcTextBox.Text);
                    }
                    catch
                    {
                        MessageBox.Show("Error in Input");
                        calcTextBox.Text = final.ToString();
                        final = 0;
                        numsTBA.Clear();
                    }
                    calcTextBox.Text = final.ToString();
                    final = 0;
                    numsTBA.Clear();
                    break;
                    
            }
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }
    }
}
