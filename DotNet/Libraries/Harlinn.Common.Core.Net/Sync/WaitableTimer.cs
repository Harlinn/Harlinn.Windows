using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Runtime.InteropServices;
using System.Threading;

namespace Harlinn.Common.Core.Net.Sync
{
    [Flags]
    public enum WaitableTimerFlags : uint 
    { 
        None = 0,
        ManualReset = 0x00000001,
        HighResolution = 0x00000002
    }

    [Flags]
    public enum WaitableTimerRights : uint
    { 
        None = 0,
        Delete = 0x00010000,
        ReadPermissions = 0x00020000, 
        ChangePermissions = 0x00040000, 
        TakeOwnership = 0x00080000,
        Synchronize = 0x00100000,
        Query = 0x0001,
        Modify = 0x0002,
        FullControl = 0x000F0000 | Synchronize | Query | Modify
    }



    public class WaitableTimer : IDisposable 
    {
        public const uint INFINITE = 0xFFFFFFFF;

        public delegate void TimerCompleteDelegate(IntPtr argToCompletionRoutine);


        [DllImport("kernel32.dll",SetLastError = true, CharSet = CharSet.Auto)]
        static extern IntPtr CreateWaitableTimerExW(IntPtr securityAttributes, string timerName, uint flags, uint desiredAccess );

        [DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Auto)]
        static extern IntPtr OpenWaitableTimer(uint desiredAccess, bool inheritHandle, string timerName);


        [DllImport("kernel32.dll", SetLastError = true)]
        static extern bool SetWaitableTimer(IntPtr timerHandle, [In] ref long filetime, uint intervalInMs, TimerCompleteDelegate completionRoutine, IntPtr argToCompletionRoutine, bool resumeSystemIfSuspended);

        [DllImport("kernel32.dll", SetLastError = true, ExactSpelling = true)]
        static extern Int32 WaitForSingleObject(IntPtr Handle, uint Wait);

        [DllImport("kernel32.dll", SetLastError = true)]
        static extern bool CancelWaitableTimer(IntPtr hTimer);

        [DllImport("kernel32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        static extern bool CloseHandle(IntPtr handle);


        static IntPtr Create(IntPtr securityAttributes, bool manualReset, bool highResolution, WaitableTimerRights desiredAccess, string name)
        {
            WaitableTimerFlags flags = manualReset ? WaitableTimerFlags.ManualReset : WaitableTimerFlags.None;
            if (highResolution)
            {
                flags |= WaitableTimerFlags.HighResolution;
            }

            var result = CreateWaitableTimerExW(securityAttributes, name, (uint)flags, (uint)desiredAccess);
            if (result.CompareTo(IntPtr.Zero) == 0 )
            {
                throw new Win32Exception(Marshal.GetLastWin32Error());
            }
            return result;
        }

        static IntPtr Open(WaitableTimerRights desiredAccess, bool inheritHandle, string name)
        {
            var result = OpenWaitableTimer((uint)desiredAccess, inheritHandle, name);
            if (result.CompareTo(IntPtr.Zero) == 0)
            {
                throw new Win32Exception(Marshal.GetLastWin32Error());
            }
            return result;
        }

        static IntPtr TryOpen(WaitableTimerRights desiredAccess, bool inheritHandle, string name)
        {
            var result = OpenWaitableTimer((uint)desiredAccess, inheritHandle, name);
            return result;
        }

        private IntPtr _handle;
        private bool _disposedValue;

        WaitableTimer(IntPtr handle)
        {
            _handle = handle;
        }

        public WaitableTimer()
            : this(Create(IntPtr.Zero, true, false, WaitableTimerRights.FullControl, null))
        {
        }

        public WaitableTimer(bool manualReset, bool highResolution = false, WaitableTimerRights desiredAccess = WaitableTimerRights.FullControl)
            : this(Create(IntPtr.Zero, manualReset, highResolution, desiredAccess, null))
        {
        }

        public WaitableTimer(string name, bool manualReset = true, bool highResolution = false, WaitableTimerRights desiredAccess = WaitableTimerRights.FullControl)
            : this(Create(IntPtr.Zero, manualReset, highResolution, desiredAccess, name))
        {
        }


        public WaitableTimer(bool manualReset, bool highResolution, WaitableTimerRights desiredAccess, IntPtr securityAttributes)
            : this(Create(securityAttributes, manualReset, highResolution, desiredAccess, null))
        {
        }

        public WaitableTimer(string name, bool manualReset, bool highResolution, WaitableTimerRights desiredAccess, IntPtr securityAttributes)
            : this(Create(securityAttributes, manualReset, highResolution, desiredAccess, name))
        {
        }

        protected virtual void Dispose(bool disposing)
        {
            if (!_disposedValue)
            {
                if (_handle.CompareTo(IntPtr.Zero) != 0)
                {
                    CloseHandle(_handle);
                    _handle = IntPtr.Zero;
                }
                _disposedValue = true;
            }
        }

        ~WaitableTimer()
        {
            Dispose(false);
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }


        public static WaitableTimer OpenExisting(string name, WaitableTimerRights desiredAccess = WaitableTimerRights.Synchronize | WaitableTimerRights.Modify, bool inheritHandle = false)
        {
            var handle = Open(desiredAccess, inheritHandle, name);
            return new WaitableTimer(handle);
        }

        public static WaitableTimer TryOpenExisting(string name, WaitableTimerRights desiredAccess = WaitableTimerRights.Synchronize | WaitableTimerRights.Modify, bool inheritHandle = false)
        {
            var handle = TryOpen(desiredAccess, inheritHandle, name);
            if (handle.CompareTo(IntPtr.Zero) != 0)
            {
                return new WaitableTimer(handle);
            }
            else
            {
                return null;
            }
        }

        public void SetTimer(long dueTime, uint intervalInMs, TimerCompleteDelegate completionRoutine, IntPtr argToCompletionRoutine, bool resumeSystemIfSuspended)
        {
            if (SetWaitableTimer(_handle, ref dueTime, intervalInMs, completionRoutine, argToCompletionRoutine, resumeSystemIfSuspended) == false)
            {
                throw new Win32Exception(Marshal.GetLastWin32Error());
            }
        }

        public void SetTimer(long dueTime, uint intervalInMs, bool resumeSystemIfSuspended)
        {
            SetTimer(dueTime, intervalInMs, null, IntPtr.Zero, resumeSystemIfSuspended);
        }


        public void SetTimer(DateTime dueTime, uint intervalInMs, bool resumeSystemIfSuspended)
        {
            long filetime = dueTime.ToFileTimeUtc();
            SetTimer(filetime,intervalInMs, resumeSystemIfSuspended);
        }

        public void SetTimer(TimeSpan dueTime, uint intervalInMs, bool resumeSystemIfSuspended)
        {
            long ticks = -dueTime.Ticks;
            SetTimer(ticks, intervalInMs, resumeSystemIfSuspended);
        }
        public void SetTimer(DateTime dueTime, TimeSpan interval, bool resumeSystemIfSuspended)
        {
            long filetime = dueTime.ToFileTimeUtc();
            uint intervalInMs = Convert.ToUInt32( interval.Duration().Ticks / TimeSpan.TicksPerMillisecond );
            SetTimer(filetime, intervalInMs, resumeSystemIfSuspended);
        }

        public void SetTimer(TimeSpan dueTime, TimeSpan interval, bool resumeSystemIfSuspended)
        {
            long ticks = -dueTime.Ticks;
            uint intervalInMs = Convert.ToUInt32(interval.Duration().Ticks / TimeSpan.TicksPerMillisecond);
            SetTimer(ticks, intervalInMs, resumeSystemIfSuspended);
        }

        public void Cancel()
        {
            if (CancelWaitableTimer(_handle) == false)
            {
                throw new Win32Exception(Marshal.GetLastWin32Error());
            }
        }

        public bool Wait(uint timeoutInMs)
        {
            var rc = WaitForSingleObject(_handle, timeoutInMs);
            switch (rc)
            {
                case 0:
                    return true;
                case 0x00000102: //timeout
                    return false;
                case 0x00000080: // abandoned
                    return false;
                default:
                    throw new Win32Exception(Marshal.GetLastWin32Error());
            }
        }

        public bool Wait(TimeSpan timeout)
        {
            uint timeoutInMs = Convert.ToUInt32(timeout.Duration().Ticks / TimeSpan.TicksPerMillisecond);
            return Wait(timeoutInMs);
        }
        public bool Wait()
        {
            return Wait(INFINITE);
        }
    }

}
