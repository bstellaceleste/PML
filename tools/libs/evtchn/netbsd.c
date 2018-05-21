/******************************************************************************
 *
 * Copyright 2006 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation;
 * version 2.1 of the License.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; If not, see <http://www.gnu.org/licenses/>.
 *
 * Split out from xc_netbsd.c
 */

#include <fcntl.h>
#include <unistd.h>

#include <sys/ioctl.h>

#include <xen/sys/evtchn.h>

#include "private.h"

#define EVTCHN_DEV_NAME  "/dev/xenevt"

int osdep_evtchn_open(xenevtchn_handle *xce)
{
    int fd = open(EVTCHN_DEV_NAME, O_NONBLOCK|O_RDWR);
    if ( fd == -1 )
        return -1;
    xce->fd = fd;
    return 0;
}

int osdep_evtchn_close(xenevtchn_handle *xce)
{
    if ( xce->fd == -1 )
        return 0;

    return close(xce->fd);
}

int xenevtchn_fd(xenevtchn_handle *xce)
{
    return xce->fd;
}

int xenevtchn_notify(xenevtchn_handle *xce, evtchn_port_t port)
{
    int fd = xce->fd;
    struct ioctl_evtchn_notify notify;

    notify.port = port;

    return ioctl(fd, IOCTL_EVTCHN_NOTIFY, &notify);
}

xenevtchn_port_or_error_t xenevtchn_bind_unbound_port(xenevtchn_handle * xce, uint32_t domid)
{
    int fd = xce->fd;
    struct ioctl_evtchn_bind_unbound_port bind;
    int ret;

    bind.remote_domain = domid;

    ret = ioctl(fd, IOCTL_EVTCHN_BIND_UNBOUND_PORT, &bind);
    if (ret == 0)
        return bind.port;
    else
        return -1;
}

xenevtchn_port_or_error_t xenevtchn_bind_interdomain(xenevtchn_handle *xce, uint32_t domid,
                                                  evtchn_port_t remote_port)
{
    int fd = xce->fd;
    struct ioctl_evtchn_bind_interdomain bind;
    int ret;

    bind.remote_domain = domid;
    bind.remote_port = remote_port;

    ret = ioctl(fd, IOCTL_EVTCHN_BIND_INTERDOMAIN, &bind);
    if (ret == 0)
        return bind.port;
    else
        return -1;
}

int xenevtchn_unbind(xenevtchn_handle *xce, evtchn_port_t port)
{
    int fd = xce->fd;
    struct ioctl_evtchn_unbind unbind;

    unbind.port = port;

    return ioctl(fd, IOCTL_EVTCHN_UNBIND, &unbind);
}

xenevtchn_port_or_error_t xenevtchn_bind_virq(xenevtchn_handle *xce, unsigned int virq)
{
    int fd = xce->fd;
    struct ioctl_evtchn_bind_virq bind;
    int err;

    bind.virq = virq;

    err = ioctl(fd, IOCTL_EVTCHN_BIND_VIRQ, &bind);
    if (err)
        return -1;
    else
        return bind.port;
}

xenevtchn_port_or_error_t xenevtchn_pending(xenevtchn_handle *xce)
{
    int fd = xce->fd;
    evtchn_port_t port;

    if ( read_exact(fd, (char *)&port, sizeof(port)) == -1 )
        return -1;

    return port;
}

int xenevtchn_unmask(xenevtchn_handle *xce, evtchn_port_t port)
{
    int fd = xce->fd;
    return write_exact(fd, (char *)&port, sizeof(port));
}

/*
 * Local variables:
 * mode: C
 * c-file-style: "BSD"
 * c-basic-offset: 4
 * tab-width: 4
 * indent-tabs-mode: nil
 * End:
 */
