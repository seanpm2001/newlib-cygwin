/* wincap.h: Header for OS capability class.

This file is part of Cygwin.

This software is a copyrighted work licensed under the terms of the
Cygwin license.  Please consult the file "CYGWIN_LICENSE" for
details. */

#ifndef _WINCAP_H
#define _WINCAP_H

struct wincaps
{
  DWORD def_guard_pages;
  int64_t mmap_storage_high;
  /* The bitfields must be 8 byte aligned on x86_64, otherwise the bitfield
     ops generated by gcc are off by 4 bytes. */
  struct  __attribute__ ((aligned (8))) {
    unsigned is_server				: 1;
    unsigned needs_count_in_si_lpres2		: 1;
    unsigned needs_query_information		: 1;
    unsigned has_gaa_largeaddress_bug		: 1;
    unsigned has_broken_alloc_console		: 1;
    unsigned has_console_logon_sid		: 1;
    unsigned has_precise_system_time		: 1;
    unsigned has_microsoft_accounts		: 1;
    unsigned has_processor_groups		: 1;
    unsigned has_broken_prefetchvm		: 1;
    unsigned has_new_pebteb_region		: 1;
    unsigned has_broken_whoami			: 1;
    unsigned has_unprivileged_createsymlink	: 1;
    unsigned has_unbiased_interrupt_time	: 1;
    unsigned has_precise_interrupt_time		: 1;
    unsigned has_posix_unlink_semantics		: 1;
    unsigned has_case_sensitive_dirs		: 1;
    unsigned has_posix_rename_semantics		: 1;
    unsigned no_msv1_0_s4u_logon_in_wow64	: 1;
    unsigned has_con_24bit_colors		: 1;
    unsigned has_con_broken_csi3j		: 1;
    unsigned has_con_broken_il_dl		: 1;
    unsigned has_con_esc_rep			: 1;
    unsigned has_extended_mem_api		: 1;
    unsigned has_tcp_fastopen			: 1;
    unsigned has_linux_tcp_keepalive_sockopts	: 1;
    unsigned has_tcp_maxrtms			: 1;
  };
};

class wincapc
{
  SYSTEM_INFO		system_info;
  RTL_OSVERSIONINFOEXW	version;
  char			osnam[40];
  ULONG_PTR		wow64;
  void			*caps;

public:
  void init ();

  const DWORD cpu_count () const { return system_info.dwNumberOfProcessors; }
  const DWORD_PTR cpu_mask () const { return system_info.dwActiveProcessorMask;}

  const WORD cpu_arch () const { return system_info.wProcessorArchitecture; }
  const WORD cpu_level () const { return system_info.wProcessorLevel; }

  /* The casts to size_t make sure that the returned value has the size of
     a pointer on any system.  This is important when using them for bit
     mask operations, like in roundup2. */
  const size_t page_size () const { return (size_t) system_info.dwPageSize; }
  const size_t allocation_granularity () const
		     { return (size_t) system_info.dwAllocationGranularity; }
  const char *osname () const { return osnam; }
  const DWORD build_number () const { return version.dwBuildNumber; }
  const bool is_wow64 () const { return !!wow64; }

#define IMPLEMENT(cap) cap() const { return ((wincaps *) this->caps)->cap; }

  DWORD def_guard_page_size () const
  {
    return ((wincaps *) this->caps)->def_guard_pages * page_size ();
  }
#ifdef __x86_64__
  intptr_t IMPLEMENT (mmap_storage_high)
#endif
  bool  IMPLEMENT (is_server)
  bool	IMPLEMENT (needs_count_in_si_lpres2)
  bool	IMPLEMENT (needs_query_information)
  bool	IMPLEMENT (has_gaa_largeaddress_bug)
  bool	IMPLEMENT (has_broken_alloc_console)
  bool	IMPLEMENT (has_console_logon_sid)
  bool	IMPLEMENT (has_precise_system_time)
  bool	IMPLEMENT (has_microsoft_accounts)
  bool	IMPLEMENT (has_processor_groups)
  bool	IMPLEMENT (has_broken_prefetchvm)
  bool	IMPLEMENT (has_new_pebteb_region)
  bool	IMPLEMENT (has_broken_whoami)
  bool	IMPLEMENT (has_unprivileged_createsymlink)
  bool	IMPLEMENT (has_unbiased_interrupt_time)
  bool	IMPLEMENT (has_precise_interrupt_time)
  bool	IMPLEMENT (has_posix_unlink_semantics)
  bool	IMPLEMENT (has_case_sensitive_dirs)
  bool	IMPLEMENT (has_posix_rename_semantics)
  bool	IMPLEMENT (no_msv1_0_s4u_logon_in_wow64)
  bool	IMPLEMENT (has_con_24bit_colors)
  bool	IMPLEMENT (has_con_broken_csi3j)
  bool	IMPLEMENT (has_con_broken_il_dl)
  bool	IMPLEMENT (has_con_esc_rep)
  bool	IMPLEMENT (has_extended_mem_api)
  bool	IMPLEMENT (has_tcp_fastopen)
  bool	IMPLEMENT (has_linux_tcp_keepalive_sockopts)
  bool	IMPLEMENT (has_tcp_maxrtms)

  void disable_case_sensitive_dirs ()
  {
    ((wincaps *)caps)->has_case_sensitive_dirs = false;
  }
#undef IMPLEMENT
};

extern wincapc wincap;

#endif /* _WINCAP_H */
