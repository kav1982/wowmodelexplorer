﻿using System;
using System.ComponentModel;
using System.Windows;
using System.Windows.Input;
using WowTexViewer.Controls;
using System.Threading;
using System.Windows.Threading;
using WowTexViewer.Controls.Splash;
using WowTexViewer.Services;
using AvalonDock;
using mywowNet;
using WowTexViewer.Commands;
using WowTexViewer.Properties;
using WowTexViewer.Utility;

namespace WowTexViewer
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private readonly DispatcherTimer timer;
        private WindowHost windowhost;
        private bool isKeyFocus = false;
        private bool isBackMode = false;

        public MainWindow()
        {
            InitializeComponent();

            Loaded += new RoutedEventHandler(MainWindow_Loaded);
            Closing += new CancelEventHandler(MainWindow_Closing);
            StateChanged += new EventHandler(MainWindow_StateChanged);
            LostKeyboardFocus += delegate { isKeyFocus = false; };

            timer = new DispatcherTimer(DispatcherPriority.ApplicationIdle);
            timer.Interval = new System.TimeSpan(0, 0, 0, 0, 1);
            timer.Tick += new EventHandler(timer_Tick);

#if WOW50
            this.Title = "WowTexViewer (wow version 5.x)";
#elif WOW60
            this.Title = "WowTexViewer (wow version 6.x)";
#else
            this.Title = "WowTexViewer (wow version 7.x)";
#endif
        }

        public bool IsKeyFocus
        {
            get { return isKeyFocus; }
            set { isKeyFocus = value; }
        }

        public bool IsMaximized
        {
            get { return WindowState == WindowState.Maximized; }
            set
            {
                if (value)
                {
                    WindowState = WindowState.Maximized;
                }
                else if (WindowState == WindowState.Maximized)
                {
                    WindowState = WindowState.Normal;
                }
            }
        }

        public bool IsBackMode
        {
            get { return isBackMode;  }
        }

        private void InitCommandBindings()
        {
            CommandBindings.AddRange(ShellService.Instance.FileCommands.CommandBindings);

            CommandBindings.AddRange(ShellService.Instance.ViewCommands.CommandBindings);

            CommandBindings.AddRange(ShellService.Instance.TextureCommands.CommandBindings);

            CommandBindings.AddRange(ShellService.Instance.OptionCommandds.CommandBindings);

            CommandBindings.AddRange(ShellService.Instance.LuaguageCommands.CommandBindings);
        }

        private void MainWindow_Loaded(object sender, RoutedEventArgs e)
        {
            this.Loaded -= MainWindow_Loaded;

            SplashWindow _splash = new SplashWindow();
            _splash.Show();

            MessageListener.Instance.StartWork(GetStageText(0), new DispatcherOperationCallback(InitStage0));
            Thread.Sleep(1);

            MessageListener.Instance.StartWork(GetStageText(1), new DispatcherOperationCallback(InitStage1));
            Thread.Sleep(1);

            MessageListener.Instance.StartWork(GetStageText(2), new DispatcherOperationCallback(InitStage2));
            Thread.Sleep(1);

            _splash.Close();
        }

        private string GetStageText(int index)
        {
            switch (index)
            {
                case 0:
                    return Application.Current.FindResource("stage1") as string;
                case 1:
                    return Application.Current.FindResource("stage2") as string;
                case 2:
                    return Application.Current.FindResource("stage3") as string;
            }
            return "";
        }

        private object InitStage0(object frame)
        {
            IntPtr hwnd = EngineService.Instance.InitilalizeEngine();
            windowhost = new WindowHost(hwnd);

            ModelSceneService.Instance.Initialize();

            windowhost.WmResize += new ResizeEventHandler(windowHost_WmResize);
            windowhost.WmMouse += new MouseMessageHandler(windowHost_WmMouse);

            ((DispatcherFrame)frame).Continue = false;
            return null;
        }

        private object InitStage1(object frame)
        {
            EngineService.Instance.RetrieveWowData();

            ((DispatcherFrame)frame).Continue = false;
            return null;
        }

        private object InitStage2(object frame)
        {
            InitCommandBindings();

            _allTextureContent.Initialize();
            _mapTexContent.Initialize();

            //model mode
            if (windowhost.HWnd != IntPtr.Zero)
            {
                _controlHostElement.Child = windowhost;
            }

            _leftDockablePane.SetValue(ResizingPanel.ResizeWidthProperty, new GridLength(300));
            _rightDockablePane.SetValue(ResizingPanel.ResizeWidthProperty, new GridLength(300));

            _allTextureContent.Activate();

            timer.Start();

            ((DispatcherFrame)frame).Continue = false;
            return null;
        }

        private void MainWindow_Closing(object sender, CancelEventArgs e)
        {
            if (!e.Cancel)
            {
                timer.Stop();
            }

            ModelSceneService.Instance.Shutdown();
            EngineService.Instance.Shutdown();
        }

        private void timer_Tick(object sender, EventArgs e)
        {
            //update scene
            EngineService.Instance.Tick();
      }

        private object _tick_UI(object param)
        {
            return null;
        }

        private void windowHost_WmResize(object sender, uint w, uint h)
        {
            if (w == 0 || h == 0)
                isBackMode = true;
            else
            {
                isBackMode = false;

                EngineService.Instance.OnResize(w, h);
            }
        }

        private void windowHost_WmMouse(object sender, MouseMessage msg, int x, int y, short zDelta)
        {
            if (msg == MouseMessage.MouseLButtonDown ||
                msg == MouseMessage.MouseLButtonUp ||
                msg == MouseMessage.MouseRButtonDown ||
                msg == MouseMessage.MouseRButtonUp)
            {
                if (!isKeyFocus)
                {
                    Keyboard.Focus(this);
                    NativeMethods.SetFocus(windowhost.HWnd);
                    isKeyFocus = true;
                }
            }

            EngineService.Instance.OnMouseMessage(msg, x, y, zDelta);
        }

        private void MainWindow_StateChanged(object sender, EventArgs e)
        {
            timer.IsEnabled = WindowState != WindowState.Minimized;
        }

    }
}
