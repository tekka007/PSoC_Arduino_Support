﻿//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:4.0.30319.18444
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

namespace Bootloader_v1_30.Properties {
    using System;
    
    
    /// <summary>
    ///   A strongly-typed resource class, for looking up localized strings, etc.
    /// </summary>
    // This class was auto-generated by the StronglyTypedResourceBuilder
    // class via a tool like ResGen or Visual Studio.
    // To add or remove a member, edit your .ResX file then rerun ResGen
    // with the /str option, or rebuild your VS project.
    [global::System.CodeDom.Compiler.GeneratedCodeAttribute("System.Resources.Tools.StronglyTypedResourceBuilder", "4.0.0.0")]
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute()]
    [global::System.Runtime.CompilerServices.CompilerGeneratedAttribute()]
    public class Resources {
        
        private static global::System.Resources.ResourceManager resourceMan;
        
        private static global::System.Globalization.CultureInfo resourceCulture;
        
        [global::System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1811:AvoidUncalledPrivateCode")]
        internal Resources() {
        }
        
        /// <summary>
        ///   Returns the cached ResourceManager instance used by this class.
        /// </summary>
        [global::System.ComponentModel.EditorBrowsableAttribute(global::System.ComponentModel.EditorBrowsableState.Advanced)]
        public static global::System.Resources.ResourceManager ResourceManager {
            get {
                if (object.ReferenceEquals(resourceMan, null)) {
                    global::System.Resources.ResourceManager temp = new global::System.Resources.ResourceManager("Bootloader_v1_30.Properties.Resources", typeof(Resources).Assembly);
                    resourceMan = temp;
                }
                return resourceMan;
            }
        }
        
        /// <summary>
        ///   Overrides the current thread's CurrentUICulture property for all
        ///   resource lookups using this strongly typed resource class.
        /// </summary>
        [global::System.ComponentModel.EditorBrowsableAttribute(global::System.ComponentModel.EditorBrowsableState.Advanced)]
        public static global::System.Globalization.CultureInfo Culture {
            get {
                return resourceCulture;
            }
            set {
                resourceCulture = value;
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Bootloader component configuration does not match Application Type of the project. The Multi-Application Bootloader option must correspond project Application Type..
        /// </summary>
        public static string AppTypeCompareError {
            get {
                return ResourceManager.GetString("AppTypeCompareError", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Enter {0}-byte hexadecimal value.
        /// </summary>
        public static string ErrTBFormat {
            get {
                return ResourceManager.GetString("ErrTBFormat", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Value range is from {0} to {1}.
        /// </summary>
        public static string ErrTBRange {
            get {
                return ResourceManager.GetString("ErrTBRange", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Some fields have wrong value.
        /// </summary>
        public static string ErrTBWrongValue {
            get {
                return ResourceManager.GetString("ErrTBWrongValue", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The value should be a multiple of 100.
        /// </summary>
        public static string ErrWaitTime10x {
            get {
                return ResourceManager.GetString("ErrWaitTime10x", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Interconnect.
        /// </summary>
        public static string InterconnectTabDisplayName {
            get {
                return ResourceManager.GetString("InterconnectTabDisplayName", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Built-in.
        /// </summary>
        public static string PageTitleBuiltIn {
            get {
                return ResourceManager.GetString("PageTitleBuiltIn", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Dependencies.
        /// </summary>
        public static string PageTitleDependencies {
            get {
                return ResourceManager.GetString("PageTitleDependencies", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to General.
        /// </summary>
        public static string PageTitleGeneral {
            get {
                return ResourceManager.GetString("PageTitleGeneral", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Application Version {0}.
        /// </summary>
        public static string SBComponentBodyText {
            get {
                return ResourceManager.GetString("SBComponentBodyText", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Bootloader.
        /// </summary>
        public static string SBComponentTitle {
            get {
                return ResourceManager.GetString("SBComponentTitle", resourceCulture);
            }
        }
    }
}