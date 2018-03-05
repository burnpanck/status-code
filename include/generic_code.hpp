/* Proposed SG14 status_code
(C) 2018 Niall Douglas <http://www.nedproductions.biz/> (5 commits)
File Created: Feb 2018


Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License in the accompanying file
Licence.txt or at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.


Distributed under the Boost Software License, Version 1.0.
(See accompanying file Licence.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef SYSTEM_ERROR2_GENERIC_CODE_HPP
#define SYSTEM_ERROR2_GENERIC_CODE_HPP

#include "status_error.hpp"

#include <cerrno>  // for error constants

SYSTEM_ERROR2_NAMESPACE_BEGIN

//! The generic error coding (POSIX)
enum class errc : int
{
  success = 0,
  unknown = -1,

  address_family_not_supported = EAFNOSUPPORT,
  address_in_use = EADDRINUSE,
  address_not_available = EADDRNOTAVAIL,
  already_connected = EISCONN,
  argument_list_too_long = E2BIG,
  argument_out_of_domain = EDOM,
  bad_address = EFAULT,
  bad_file_descriptor = EBADF,
  bad_message = EBADMSG,
  broken_pipe = EPIPE,
  connection_aborted = ECONNABORTED,
  connection_already_in_progress = EALREADY,
  connection_refused = ECONNREFUSED,
  connection_reset = ECONNRESET,
  cross_device_link = EXDEV,
  destination_address_required = EDESTADDRREQ,
  device_or_resource_busy = EBUSY,
  directory_not_empty = ENOTEMPTY,
  executable_format_error = ENOEXEC,
  file_exists = EEXIST,
  file_too_large = EFBIG,
  filename_too_long = ENAMETOOLONG,
  function_not_supported = ENOSYS,
  host_unreachable = EHOSTUNREACH,
  identifier_removed = EIDRM,
  illegal_byte_sequence = EILSEQ,
  inappropriate_io_control_operation = ENOTTY,
  interrupted = EINTR,
  invalid_argument = EINVAL,
  invalid_seek = ESPIPE,
  io_error = EIO,
  is_a_directory = EISDIR,
  message_size = EMSGSIZE,
  network_down = ENETDOWN,
  network_reset = ENETRESET,
  network_unreachable = ENETUNREACH,
  no_buffer_space = ENOBUFS,
  no_child_process = ECHILD,
  no_link = ENOLINK,
  no_lock_available = ENOLCK,
  no_message = ENOMSG,
  no_protocol_option = ENOPROTOOPT,
  no_space_on_device = ENOSPC,
  no_stream_resources = ENOSR,
  no_such_device_or_address = ENXIO,
  no_such_device = ENODEV,
  no_such_file_or_directory = ENOENT,
  no_such_process = ESRCH,
  not_a_directory = ENOTDIR,
  not_a_socket = ENOTSOCK,
  not_a_stream = ENOSTR,
  not_connected = ENOTCONN,
  not_enough_memory = ENOMEM,
  not_supported = ENOTSUP,
  operation_cancelled = ECANCELED,
  operation_in_progress = EINPROGRESS,
  operation_not_permitted = EPERM,
  operation_not_supported = EOPNOTSUPP,
  operation_would_block = EWOULDBLOCK,
  owner_dead = EOWNERDEAD,
  permission_denied = EACCES,
  protcol_error = EPROTO,
  protocol_not_supported = EPROTONOSUPPORT,
  read_only_file_system = EROFS,
  resource_deadlock_would_occur = EDEADLK,
  resource_unavailable_try_again = EAGAIN,
  result_out_of_range = ERANGE,
  state_not_recoverable = ENOTRECOVERABLE,
  stream_timeout = ETIME,
  text_file_busy = ETXTBSY,
  timed_out = ETIMEDOUT,
  too_many_files_open_in_system = ENFILE,
  too_many_files_open = EMFILE,
  too_many_links = EMLINK,
  too_many_symbolic_link_levels = ELOOP,
  value_too_large = EOVERFLOW,
  wrong_protocol_type = EPROTOTYPE
};

namespace detail
{
  struct generic_code_messages
  {
    const char *msgs[256];
    SYSTEM_ERROR2_CONSTEXPR14 size_t size() const { return sizeof(msgs) / sizeof(*msgs); }
    SYSTEM_ERROR2_CONSTEXPR14 const char *operator[](int i) const { return (i < 0 || i >= static_cast<int>(size()) || nullptr == msgs[i]) ? "unknown" : msgs[i]; }  // NOLINT
    SYSTEM_ERROR2_CONSTEXPR14 generic_code_messages()
        : msgs{}
    {
      msgs[0] = "Success";

      msgs[EAFNOSUPPORT] = "Address family not supported by protocol";
      msgs[EADDRINUSE] = "Address already in use";
      msgs[EADDRNOTAVAIL] = "Cannot assign requested address";
      msgs[EISCONN] = "Transport endpoint is already connected";
      msgs[E2BIG] = "Argument list too long";
      msgs[EDOM] = "Numerical argument out of domain";
      msgs[EFAULT] = "Bad address";
      msgs[EBADF] = "Bad file descriptor";
      msgs[EBADMSG] = "Bad message";
      msgs[EPIPE] = "Broken pipe";
      msgs[ECONNABORTED] = "Software caused connection abort";
      msgs[EALREADY] = "Operation already in progress";
      msgs[ECONNREFUSED] = "Connection refused";
      msgs[ECONNRESET] = "Connection reset by peer";
      msgs[EXDEV] = "Invalid cross-device link";
      msgs[EDESTADDRREQ] = "Destination address required";
      msgs[EBUSY] = "Device or resource busy";
      msgs[ENOTEMPTY] = "Directory not empty";
      msgs[ENOEXEC] = "Exec format error";
      msgs[EEXIST] = "File exists";
      msgs[EFBIG] = "File too large";
      msgs[ENAMETOOLONG] = "File name too long";
      msgs[ENOSYS] = "Function not implemented";
      msgs[EHOSTUNREACH] = "No route to host";
      msgs[EIDRM] = "Identifier removed";
      msgs[EILSEQ] = "Invalid or incomplete multibyte or wide character";
      msgs[ENOTTY] = "Inappropriate ioctl for device";
      msgs[EINTR] = "Interrupted system call";
      msgs[EINVAL] = "Invalid argument";
      msgs[ESPIPE] = "Illegal seek";
      msgs[EIO] = "Input/output error";
      msgs[EISDIR] = "Is a directory";
      msgs[EMSGSIZE] = "Message too long";
      msgs[ENETDOWN] = "Network is down";
      msgs[ENETRESET] = "Network dropped connection on reset";
      msgs[ENETUNREACH] = "Network is unreachable";
      msgs[ENOBUFS] = "No buffer space available";
      msgs[ECHILD] = "No child processes";
      msgs[ENOLINK] = "Link has been severed";
      msgs[ENOLCK] = "No locks available";
      msgs[ENOMSG] = "No message of desired type";
      msgs[ENOPROTOOPT] = "Protocol not available";
      msgs[ENOSPC] = "No space left on device";
      msgs[ENOSR] = "Out of streams resources";
      msgs[ENXIO] = "No such device or address";
      msgs[ENODEV] = "No such device";
      msgs[ENOENT] = "No such file or directory";
      msgs[ESRCH] = "No such process";
      msgs[ENOTDIR] = "Not a directory";
      msgs[ENOTSOCK] = "Socket operation on non-socket";
      msgs[ENOSTR] = "Device not a stream";
      msgs[ENOTCONN] = "Transport endpoint is not connected";
      msgs[ENOMEM] = "Cannot allocate memory";
      msgs[ENOTSUP] = "Operation not supported";
      msgs[ECANCELED] = "Operation canceled";
      msgs[EINPROGRESS] = "Operation now in progress";
      msgs[EPERM] = "Operation not permitted";
      msgs[EOPNOTSUPP] = "Operation not supported";
      msgs[EWOULDBLOCK] = "Resource temporarily unavailable";
      msgs[EOWNERDEAD] = "Owner died";
      msgs[EACCES] = "Permission denied";
      msgs[EPROTO] = "Protocol error";
      msgs[EPROTONOSUPPORT] = "Protocol not supported";
      msgs[EROFS] = "Read-only file system";
      msgs[EDEADLK] = "Resource deadlock avoided";
      msgs[EAGAIN] = "Resource temporarily unavailable";
      msgs[ERANGE] = "Numerical result out of range";
      msgs[ENOTRECOVERABLE] = "State not recoverable";
      msgs[ETIME] = "Timer expired";
      msgs[ETXTBSY] = "Text file busy";
      msgs[ETIMEDOUT] = "Connection timed out";
      msgs[ENFILE] = "Too many open files in system";
      msgs[EMFILE] = "Too many open files";
      msgs[EMLINK] = "Too many links";
      msgs[ELOOP] = "Too many levels of symbolic links";
      msgs[EOVERFLOW] = "Value too large for defined data type";
      msgs[EPROTOTYPE] = "Protocol wrong type for socket";
    }
  };
}  // namespace detail

/*! The implementation of the domain for generic status codes, those mapped by `errc` (POSIX).
*/
class _generic_code_domain : public status_code_domain
{
  template <class> friend class status_code;
  using _base = status_code_domain;

public:
  //! The value type of the generic code, which is an `errc` as per POSIX.
  using value_type = errc;
  using string_ref = _base::string_ref;

public:
  //! Default constructor
  constexpr _generic_code_domain() noexcept : _base(0x746d6354f4f733e9) {}
  _generic_code_domain(const _generic_code_domain &) = default;
  _generic_code_domain(_generic_code_domain &&) = default;
  _generic_code_domain &operator=(const _generic_code_domain &) = default;
  _generic_code_domain &operator=(_generic_code_domain &&) = default;
  ~_generic_code_domain() = default;

  //! Constexpr singleton getter. Returns the address of the constexpr generic_code_domain variable.
  static inline constexpr const _generic_code_domain *get();

  virtual _base::string_ref name() const noexcept override final { return string_ref("generic domain"); }  // NOLINT
protected:
  virtual bool _failure(const status_code<void> &code) const noexcept override final  // NOLINT
  {
    assert(code.domain() == *this);
    return static_cast<const generic_code &>(code).value() != errc::success;  // NOLINT
  }
  virtual bool _equivalent(const status_code<void> &code1, const status_code<void> &code2) const noexcept override final  // NOLINT
  {
    assert(code1.domain() == *this);
    const auto &c1 = static_cast<const generic_code &>(code1);  // NOLINT
    if(code2.domain() == *this)
    {
      const auto &c2 = static_cast<const generic_code &>(code2);  // NOLINT
      return c1.value() == c2.value();
    }
    return false;
  }
  virtual generic_code _generic_code(const status_code<void> &code) const noexcept override final  // NOLINT
  {
    assert(code.domain() == *this);
    return static_cast<const generic_code &>(code);  // NOLINT
  }
  virtual _base::string_ref _message(const status_code<void> &code) const noexcept override final  // NOLINT
  {
    assert(code.domain() == *this);
    const auto &c = static_cast<const generic_code &>(code);  // NOLINT
    static SYSTEM_ERROR2_CONSTEXPR14 detail::generic_code_messages msgs;
    return string_ref(msgs[static_cast<int>(c.value())]);
  }
  virtual void _throw_exception(const status_code<void> &code) const override final  // NOLINT
  {
    assert(code.domain() == *this);
    const auto &c = static_cast<const generic_code &>(code);  // NOLINT
    throw status_error<_generic_code_domain>(c);
  }
};
//! A constexpr source variable for the generic code domain, which is that of `errc` (POSIX). Returned by `_generic_code_domain::get()`.
constexpr _generic_code_domain generic_code_domain;
inline constexpr const _generic_code_domain *_generic_code_domain::get()
{
  return &generic_code_domain;
}
// Enable implicit construction of generic_code from errc
constexpr inline generic_code make_status_code(errc c) noexcept
{
  return generic_code(in_place, c);
}


/*************************************************************************************************************/


template <class T> inline bool status_code<void>::equivalent(const status_code<T> &o) const noexcept
{
  if(_domain && o._domain)
  {
    if(_domain->_equivalent(*this, o))
    {
      return true;
    }
    if(o._domain->_equivalent(o, *this))
    {
      return true;
    }
    generic_code c1 = o._domain->_generic_code(o);
    if(c1.value() != errc::unknown && _domain->_equivalent(*this, c1))
    {
      return true;
    }
    generic_code c2 = _domain->_generic_code(*this);
    if(c2.value() != errc::unknown && o._domain->_equivalent(o, c2))
    {
      return true;
    }
  }
  // If we are both empty, we are equivalent, otherwise not equivalent
  return (!_domain && !o._domain);
}
//! True if the status code's are semantically equal via `equivalent()`.
template <class DomainType1, class DomainType2> inline bool operator==(const status_code<DomainType1> &a, const status_code<DomainType2> &b) noexcept
{
  return a.equivalent(b);
}
//! True if the status code's are not semantically equal via `equivalent()`.
template <class DomainType1, class DomainType2> inline bool operator!=(const status_code<DomainType1> &a, const status_code<DomainType2> &b) noexcept
{
  return !a.equivalent(b);
}
//! True if the status code's are semantically equal via `equivalent()` to the generic code.
template <class DomainType1> inline bool operator==(const status_code<DomainType1> &a, errc b) noexcept
{
  return a.equivalent(generic_code(b));
}
//! True if the status code's are semantically equal via `equivalent()` to the generic code.
template <class DomainType1> inline bool operator==(errc a, const status_code<DomainType1> &b) noexcept
{
  return b.equivalent(generic_code(a));
}
//! True if the status code's are not semantically equal via `equivalent()` to the generic code.
template <class DomainType1> inline bool operator!=(const status_code<DomainType1> &a, errc b) noexcept
{
  return !a.equivalent(generic_code(b));
}
//! True if the status code's are not semantically equal via `equivalent()` to the generic code.
template <class DomainType1> inline bool operator!=(errc a, const status_code<DomainType1> &b) noexcept
{
  return !b.equivalent(generic_code(a));
}

SYSTEM_ERROR2_NAMESPACE_END

#endif
