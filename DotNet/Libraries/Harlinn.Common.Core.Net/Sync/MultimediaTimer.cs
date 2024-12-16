/*
   Copyright 2024 Espen Harlinn

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

using System;
using System.ComponentModel;
using System.Runtime.InteropServices;

namespace Harlinn.Common.Core.Net.Sync
{
    public class MultimediaTimer : IDisposable
    {
        public delegate void CallbackDelegate(uint id, uint message, IntPtr userContext, uint reserved1, uint reserved2);

        [DllImport("winmm.dll", SetLastError = true, EntryPoint = "timeSetEvent")]
        static extern uint TimeSetEvent(uint msDelay, uint msResolution, CallbackDelegate callback, IntPtr userContext, uint eventType);

        [DllImport("winmm.dll", SetLastError = true, EntryPoint = "timeKillEvent")]
        static extern void TimeKillEvent(uint uTimerId);

        private const int TimerOneShot = 0;
        private const int TimerPeriodic = 1;
        

        private bool _disposedValue;
        private volatile uint _timerId;

        // Default interval of 4 ms
        private int _interval = 4;
        // Default resolution of 4 ms
        private int _resolution = 4;

        private readonly CallbackDelegate _callback;

        public event EventHandler Elapsed;

        public MultimediaTimer()
        {
            _callback = TimerCallback;
        }


        private void ThrowIfDisposed()
        {
            if (_disposedValue)
            {
                throw new ObjectDisposedException(nameof(MultimediaTimer));
            }
        }

        protected virtual void Dispose(bool disposing)
        {
            if (!_disposedValue)
            {
                if (disposing)
                {
                    Elapsed = null;
                }

                _disposedValue = true;
                if (IsRunning)
                {
                    KillTimer();
                }
            }
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        ~MultimediaTimer()
        {
            Dispose(false);
        }

        private void KillTimer()
        {
            TimeKillEvent(_timerId);
            _timerId = 0;
        }

        private void TimerCallback(uint id, uint message, IntPtr userContext, uint reserved1, uint reserved2)
        {
            Elapsed?.Invoke(this, EventArgs.Empty);
        }

        public bool IsRunning
        {
            get
            {
                return _timerId != 0;
            }
        }

        /// <summary>
        /// The resolution of the timer in milliseconds. 
        /// </summary>
        public int Resolution
        {
            get
            {
                return _resolution;
            }
            set
            {
                ThrowIfDisposed();

                if (value < 0)
                {
                    throw new ArgumentOutOfRangeException(nameof(value));
                }

                _resolution = value;
            }
        }

        /// <summary>
        /// The interval of the timer in milliseconds.
        /// </summary>
        public int Interval
        {
            get
            {
                return _interval;
            }
            set
            {
                ThrowIfDisposed();
                if (IsRunning)
                {
                    throw new InvalidOperationException("The timer is running");
                }

                if (value < 0)
                {
                    throw new ArgumentOutOfRangeException(nameof(value));
                }

                _interval = value;
                if (Resolution > Interval)
                {
                    Resolution = value;
                }
            }
        }

        public void Start()
        {
            ThrowIfDisposed();

            if (IsRunning)
            {
                throw new InvalidOperationException("The timer is running");
            }

            _timerId = TimeSetEvent((uint)Interval, (uint)Resolution, _callback, IntPtr.Zero, TimerPeriodic);
            if (_timerId == 0)
            {
                throw new Win32Exception(Marshal.GetLastWin32Error());
            }
        }

        public void Stop()
        {
            ThrowIfDisposed();

            if (IsRunning == false)
            {
                throw new InvalidOperationException("The timer is not running");
            }
            KillTimer();

        }

    }

}
