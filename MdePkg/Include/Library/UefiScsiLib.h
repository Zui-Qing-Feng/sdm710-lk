/** @file
  Provides the functions to submit Scsi commands defined in SCSI-2 specification for scsi device.

  This library class provides the functions to submit SCSI commands defined in SCSI-2 specification
  for hard drive, CD and DVD devices that are the most common SCSI boot targets used by UEFI platforms.
  This library class depends on SCSI I/O Protocol defined in UEFI Specification and SCSI-2 industry standard.

Copyright (c) 2006 - 2008, Intel Corporation<BR>
All rights reserved. This program and the accompanying materials                          
are licensed and made available under the terms and conditions of the BSD License         
which accompanies this distribution.  The full text of the license may be found at        
http://opensource.org/licenses/bsd-license.php                                            

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,                     
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.             

**/

#ifndef __SCSI_LIB_H__
#define __SCSI_LIB_H__

#include <Protocol/ScsiIo.h>

/**
  Execute Test Unit Ready SCSI command on a specific SCSI target.

  Executes the Test Unit Ready command on the SCSI target specified by ScsiIo.
  If Timeout is zero, then this function waits indefinitely for the command to complete.
  If Timeout is greater than zero, then the command is executed and will timeout after Timeout 100 ns units.
  If ScsiIo is NULL, then ASSERT().
  If SenseDataLength is NULL, then ASSERT().
  If HostAdapterStatus is NULL, then ASSERT().
  If TargetStatus is NULL, then ASSERT().


  @param[in]     ScsiIo             A pointer to the SCSI I/O Protocol instance
                                    for the specific SCSI target.
  @param[in]     Timeout            The timeout in 100 ns units to use for the execution
                                    of this SCSI Request Packet. A Timeout value of
                                    zero means that this function will wait indefinitely
                                    for the SCSI Request Packet to execute. If Timeout
                                    is greater than zero, then this function will return
                                    EFI_TIMEOUT if the time required to execute the SCSI
                                    Request Packet is greater than Timeout.
  @param[in, out] SenseData         A pointer to sense data that was generated by
                                    the execution of the SCSI Request Packet. This
                                    buffer must be allocated by the caller.
                                    If SenseDataLength is 0, then this parameter is
                                    optional and may be NULL.
  @param[in, out] SenseDataLength   On input, a pointer to the length in bytes of
                                    the SenseData buffer. On output, a pointer to
                                    the number of bytes written to the SenseData buffer. 
  @param[out]     HostAdapterStatus The status of the SCSI Host Controller that produces
                                    the SCSI bus containing the SCSI target specified by
                                    ScsiIo when the SCSI Request Packet was executed.
                                    See the EFI SCSI I/O Protocol in the UEFI Specification
                                    for details on the possible return values.
  @param[out]     TargetStatus      The status returned by the SCSI target specified
                                    by ScsiIo when the SCSI Request Packet was executed
                                    on the SCSI Host Controller. See the EFI SCSI I/O
                                    Protocol in the UEFI Specification for details on
                                    the possible return values. 

  @retval EFI_SUCCESS          The command was executed successfully.
                               See HostAdapterStatus, TargetStatus, SenseDataLength,
                               and SenseData in that order for additional status
                               information.
  @retval EFI_NOT_READY        The SCSI Request Packet could not be sent because
                               there are too many SCSI Command Packets already
                               queued. The SCSI Request Packet was not sent, so
                               no additional status information is available.
                               The caller may retry again later.
  @retval EFI_DEVICE_ERROR     A device error occurred while attempting to send
                               SCSI Request Packet.  See HostAdapterStatus,
                               TargetStatus, SenseDataLength, and SenseData in that
                               order for additional status information.
  @retval EFI_UNSUPPORTED      The command described by the SCSI Request Packet
                               is not supported by the SCSI initiator(i.e., SCSI
                               Host Controller). The SCSI Request Packet was not
                               sent, so no additional status information is available.
  @retval EFI_TIMEOUT          A timeout occurred while waiting for the SCSI Request
                               Packet to execute.  See HostAdapterStatus, TargetStatus,
                               SenseDataLength, and SenseData in that order for
                               additional status information.

**/
EFI_STATUS
EFIAPI
ScsiTestUnitReadyCommand (
  IN     EFI_SCSI_IO_PROTOCOL  *ScsiIo,
  IN     UINT64                Timeout,
  IN OUT VOID                  *SenseData,  OPTIONAL
  IN OUT UINT8                 *SenseDataLength,
     OUT UINT8                 *HostAdapterStatus,
     OUT UINT8                 *TargetStatus
  );


/**
  Execute Inquiry SCSI command on a specific SCSI target.

  Executes the Inquiry command on the SCSI target specified by ScsiIo.
  If Timeout is zero, then this function waits indefinitely for the command to complete.
  If Timeout is greater than zero, then the command is executed and will timeout after Timeout 100 ns units.
  If ScsiIo is NULL, then ASSERT().
  If SenseDataLength is NULL, then ASSERT().
  If HostAdapterStatus is NULL, then ASSERT().
  If TargetStatus is NULL, then ASSERT().
  If InquiryDataLength is NULL, then ASSERT().

  @param[in]      ScsiIo                 A pointer to the SCSI I/O Protocol instance
                                         for the specific SCSI target.
  @param[in]      Timeout                The timeout in 100 ns units to use for the
                                         execution of this SCSI Request Packet. A Timeout
                                         value of zero means that this function will wait
                                         indefinitely for the SCSI Request Packet to execute.
                                         If Timeout is greater than zero, then this function
                                         will return EFI_TIMEOUT if the time required to
                                         execute the SCSI Request Packet is greater than Timeout.
  @param[in, out] SenseData              A pointer to sense data that was generated
                                         by the execution of the SCSI Request Packet.
                                         This buffer must be allocated by the caller.
                                         If SenseDataLength is 0, then this parameter
                                         is optional and may be NULL.
  @param[in, out] SenseDataLength        On input, the length in bytes of the SenseData buffer.
                                         On output, the number of bytes written to the SenseData buffer. 
  @param[out]     HostAdapterStatus      The status of the SCSI Host Controller that
                                         produces the SCSI bus containing the SCSI
                                         target specified by ScsiIo when the SCSI
                                         Request Packet was executed.  See the EFI
                                         SCSI I/O Protocol in the UEFI Specification
                                         for details on the possible return values.
  @param[out]     TargetStatus           The status returned by the SCSI target specified
                                         by ScsiIo when the SCSI Request Packet was
                                         executed on the SCSI Host Controller.
                                         See the EFI SCSI I/O Protocol in the UEFI
                                         Specification for details on the possible
                                         return values. 
  @param[in, out] InquiryDataBuffer      A pointer to inquiry data that was generated
                                         by the execution of the SCSI Request Packet.
                                         This buffer must be allocated by the caller.
                                         If InquiryDataLength is 0, then this parameter
                                         is optional and may be NULL. 
  @param[in, out] InquiryDataLength      On input, a pointer to the length in bytes
                                         of the InquiryDataBuffer buffer.
                                         On output, a pointer to the number of bytes
                                         written to the InquiryDataBuffer buffer.
  @param[in]      EnableVitalProductData If TRUE, then the supported vital product
                                         data is returned in InquiryDataBuffer.
                                         If FALSE, then the standard inquiry data is
                                         returned in InquiryDataBuffer. 

  @retval EFI_SUCCESS          The command was executed successfully. See HostAdapterStatus,
                               TargetStatus, SenseDataLength, and SenseData in that order
                               for additional status information.
  @retval EFI_BAD_BUFFER_SIZE  The SCSI Request Packet was executed, but the entire
                               InquiryDataBuffer could not be transferred. The actual
                               number of bytes transferred is returned in InquiryDataLength.
  @retval EFI_NOT_READY        The SCSI Request Packet could not be sent because there
                               are too many SCSI Command Packets already queued.
                               The SCSI Request Packet was not sent, so no additional
                               status information is available. The caller may retry again later.
  @retval EFI_DEVICE_ERROR     A device error occurred while attempting to send SCSI
                               Request Packet.  See HostAdapterStatus, TargetStatus,
                               SenseDataLength, and SenseData in that order for additional
                               status information.
  @retval EFI_UNSUPPORTED      The command described by the SCSI Request Packet is not
                               supported by the SCSI initiator(i.e., SCSI  Host Controller).
                               The SCSI Request Packet was not sent, so no additional
                               status information is available.
  @retval EFI_TIMEOUT          A timeout occurred while waiting for the SCSI Request
                               Packet to execute.  See HostAdapterStatus, TargetStatus,
                               SenseDataLength, and SenseData in that order for
                               additional status information.

**/
EFI_STATUS
EFIAPI
ScsiInquiryCommand (
  IN     EFI_SCSI_IO_PROTOCOL  *ScsiIo,
  IN     UINT64                Timeout,
  IN OUT VOID                  *SenseData,  OPTIONAL
  IN OUT UINT8                 *SenseDataLength,
     OUT UINT8                 *HostAdapterStatus,
     OUT UINT8                 *TargetStatus,
  IN OUT VOID                  *InquiryDataBuffer,    OPTIONAL
  IN OUT UINT32                *InquiryDataLength,
  IN     BOOLEAN               EnableVitalProductData
  );


/**
  Execute Mode Sense(10) SCSI command on a specific SCSI target.

  Executes the SCSI Mode Sense(10) command on the SCSI target specified by ScsiIo.
  If Timeout is zero, then this function waits indefinitely for the command to complete.
  If Timeout is greater than zero, then the command is executed and will timeout
  after Timeout 100 ns units.  The DBDField, PageControl, and PageCode parameters
  are used to construct the CDB for this SCSI command.
  If ScsiIo is NULL, then ASSERT().
  If SenseDataLength is NULL, then ASSERT().
  If HostAdapterStatus is NULL, then ASSERT().
  If TargetStatus is NULL, then ASSERT().
  If DataLength is NULL, then ASSERT().


  @param[in]      ScsiIo             A pointer to the SCSI I/O Protocol instance
                                     for the specific SCSI target.
  @param[in]      Timeout            The timeout in 100 ns units to use for the
                                     execution of this SCSI Request Packet. A Timeout
                                     value of zero means that this function will wait
                                     indefinitely for the SCSI Request Packet to execute.
                                     If Timeout is greater than zero, then this function
                                     will return EFI_TIMEOUT if the time required to
                                     execute the SCSI Request Packet is greater than Timeout.
  @param[in, out]  SenseData         A pointer to sense data that was generated
                                     by the execution of the SCSI Request Packet.
                                     This buffer must be allocated by the caller.
                                     If SenseDataLength is 0, then this parameter
                                     is optional and may be NULL.
  @param[in, out]  SenseDataLength   On input, the length in bytes of the SenseData buffer.
                                     On output, the number of bytes written to the SenseData buffer. 
  @param[out]     HostAdapterStatus  The status of the SCSI Host Controller that
                                     produces the SCSI bus containing the SCSI target
                                     specified by ScsiIo when the SCSI Request Packet
                                     was executed. See the EFI SCSI I/O Protocol in the
                                     UEFI Specification for details on the possible
                                     return values.
  @param[out]     TargetStatus       The status returned by the SCSI target specified
                                     by ScsiIo when the SCSI Request Packet was executed
                                     on the SCSI Host Controller.  See the EFI SCSI
                                     I/O Protocol in the UEFI Specification for details
                                     on the possible return values.
  @param[in, out]  DataBuffer        A pointer to data that was generated by the
                                     execution of the SCSI Request Packet.  This
                                     buffer must be allocated by the caller. If
                                     DataLength is 0, then this parameter is optional
                                     and may be NULL. 
  @param[in, out]  DataLength        On input, a pointer to the length in bytes of
                                     the DataBuffer buffer.  On output, a pointer
                                     to the number of bytes written to the DataBuffer
                                     buffer. 
  @param[in]      DBDField           Specifies the DBD field of the CDB for this SCSI Command.
  @param[in]      PageControl        Specifies the PC field of the CDB for this SCSI Command. 
  @param[in]      PageCode           Specifies the Page Control field of the CDB for this SCSI Command. 

  @retval EFI_SUCCESS               The command was executed successfully.
                                    See HostAdapterStatus, TargetStatus, SenseDataLength,
                                    and SenseData in that order for additional status information.
  @retval EFI_BAD_BUFFER_SIZE       The SCSI Request Packet was executed, but the
                                    entire DataBuffer could not be transferred.
                                    The actual number of bytes transferred is returned
                                    in DataLength.
  @retval EFI_NOT_READY             The SCSI Request Packet could not be sent because
                                    there are too many SCSI Command Packets already queued.
                                    The SCSI Request Packet was not sent, so no additional
                                    status information is available.  The caller may retry
                                    again later.
  @retval EFI_DEVICE_ERROR          A device error occurred while attempting to send
                                    SCSI Request Packet.  See HostAdapterStatus, TargetStatus,
                                    SenseDataLength, and SenseData in that order for
                                    additional status information.
  @retval EFI_UNSUPPORTED           The command described by the SCSI Request Packet
                                    is not supported by the SCSI initiator(i.e., SCSI
                                    Host Controller). The SCSI Request Packet was not
                                    sent, so no additional status information is available.
  @retval EFI_TIMEOUT               A timeout occurred while waiting for the SCSI
                                    Request Packet to execute.  See HostAdapterStatus,
                                    TargetStatus, SenseDataLength, and SenseData in that
                                    order for additional status information.

**/
EFI_STATUS
EFIAPI
ScsiModeSense10Command (
  IN     EFI_SCSI_IO_PROTOCOL    *ScsiIo,
  IN     UINT64                  Timeout,
  IN OUT VOID                    *SenseData,  OPTIONAL
  IN OUT UINT8                   *SenseDataLength,
     OUT UINT8                   *HostAdapterStatus,
     OUT UINT8                   *TargetStatus,
  IN OUT VOID                    *DataBuffer, OPTIONAL
  IN OUT UINT32                  *DataLength,
  IN     UINT8                   DBDField,    OPTIONAL
  IN     UINT8                   PageControl,
  IN     UINT8                   PageCode
  );



/**
  Execute Request Sense SCSI command on a specific SCSI target.

  Executes the Request Sense command on the SCSI target specified by ScsiIo.
  If Timeout is zero, then this function waits indefinitely for the command to complete.
  If Timeout is greater than zero, then the command is executed and will timeout after Timeout 100 ns units.
  If ScsiIo is NULL, then ASSERT().
  If SenseDataLength is NULL, then ASSERT().
  If HostAdapterStatus is NULL, then ASSERT().
  If TargetStatus is NULL, then ASSERT().

  @param[in]       ScsiIo               A pointer to SCSI IO protocol.
  @param[in]       Timeout              The length of timeout period.
  @param[in, out]  SenseData            A pointer to output sense data.
  @param[in, out]  SenseDataLength      The length of output sense data.
  @param[out]      HostAdapterStatus    The status of Host Adapter.
  @param[out]      TargetStatus         The status of the target.

  @retval EFI_SUCCESS                   Command is executed successfully.
  @retval EFI_NOT_READY                 The SCSI Request Packet could not be sent because there are
                                        too many SCSI Command Packets already queued.
  @retval EFI_DEVICE_ERROR              A device error occurred while attempting to send SCSI Request Packet.
  @retval EFI_UNSUPPORTED               The command described by the SCSI Request Packet is not supported by
                                        the SCSI initiator(i.e., SCSI  Host Controller)
  @retval EFI_TIMEOUT                   A timeout occurred while waiting for the SCSI Request Packet to execute.

**/
EFI_STATUS
EFIAPI
ScsiRequestSenseCommand (
  IN     EFI_SCSI_IO_PROTOCOL  *ScsiIo,
  IN     UINT64                Timeout,
  IN OUT VOID                  *SenseData,  OPTIONAL
  IN OUT UINT8                 *SenseDataLength,
     OUT UINT8                 *HostAdapterStatus,
     OUT UINT8                 *TargetStatus
  );


/**
  Execute Read Capacity SCSI command on a specific SCSI target.

  Executes the SCSI Read Capacity command on the SCSI target specified by ScsiIo.
  If Timeout is zero, then this function waits indefinitely for the command to complete.
  If Timeout is greater than zero, then the command is executed and will timeout after
  Timeout 100 ns units.  The PMI parameter is used to construct the CDB for this SCSI command.
  If ScsiIo is NULL, then ASSERT().
  If SenseDataLength is NULL, then ASSERT().
  If HostAdapterStatus is NULL, then ASSERT().
  If TargetStatus is NULL, then ASSERT().
  If DataLength is NULL, then ASSERT().

  @param[in]      ScsiIo               A pointer to SCSI IO protocol.
  @param[in]      Timeout              The length of timeout period.
  @param[in, out] SenseData            A pointer to output sense data.
  @param[in, out] SenseDataLength      The length of output sense data.
  @param[out]     HostAdapterStatus    The status of Host Adapter.
  @param[out]     TargetStatus         The status of the target.
  @param[in, out] DataBuffer           A pointer to a data buffer.
  @param[in, out] DataLength           The length of data buffer.
  @param[in]      PMI                  Partial medium indicator.

  @retval  EFI_SUCCESS           Command is executed successfully.
  @retval  EFI_BAD_BUFFER_SIZE   The SCSI Request Packet was executed, but the entire
                                 DataBuffer could not be transferred. The actual
                                 number of bytes transferred is returned in DataLength.
  @retval  EFI_NOT_READY         The SCSI Request Packet could not be sent because
                                 there are too many SCSI Command Packets already queued.
  @retval  EFI_DEVICE_ERROR      A device error occurred while attempting to send SCSI Request Packet.
  @retval  EFI_UNSUPPORTED       The command described by the SCSI Request Packet
                                 is not supported by the SCSI initiator(i.e., SCSI  Host Controller)
  @retval  EFI_TIMEOUT           A timeout occurred while waiting for the SCSI Request Packet to execute.

**/
EFI_STATUS
EFIAPI
ScsiReadCapacityCommand (
  IN     EFI_SCSI_IO_PROTOCOL  *ScsiIo,
  IN     UINT64                Timeout,
  IN OUT VOID                  *SenseData,    OPTIONAL
  IN OUT UINT8                 *SenseDataLength,
     OUT UINT8                 *HostAdapterStatus,
     OUT UINT8                 *TargetStatus,
  IN OUT VOID                  *DataBuffer,   OPTIONAL
  IN OUT UINT32                *DataLength,
  IN     BOOLEAN               PMI
  );


/**
  Function to submit read capacity16 command.

  @param  ScsiIo            A pointer to SCSI IO protocol.
  @param  Timeout           The length of timeout period.
  @param  SenseData         A pointer to output sense data.
  @param  SenseDataLength   The length of output sense data.
  @param  HostAdapterStatus The status of Host Adapter.
  @param  TargetStatus      The status of the target.
  @param  DataBuffer        A pointer to a data buffer.
  @param  DataLength        The length of data buffer.
  @param  PMI               Partial medium indicator.

  @retval  EFI_SUCCESS            The status of the unit is tested successfully.
  @retval  EFI_BAD_BUFFER_SIZE    The SCSI Request Packet was executed, 
                                  but the entire DataBuffer could not be transferred.
                                  The actual number of bytes transferred is returned
                                  in TransferLength.
  @retval  EFI_NOT_READY          The SCSI Request Packet could not be sent because 
                                  there are too many SCSI Command Packets already 
                                  queued.
  @retval  EFI_DEVICE_ERROR       A device error occurred while attempting to send 
                                  the SCSI Request Packet.
  @retval  EFI_INVALID_PARAMETER  The contents of CommandPacket are invalid.  
  @retval  EFI_UNSUPPORTED        The command described by the SCSI Request Packet
                                  is not supported by the SCSI initiator(i.e., SCSI 
                                  Host Controller).
  @retval  EFI_TIMEOUT            A timeout occurred while waiting for the SCSI 
                                  Request Packet to execute.

**/

EFI_STATUS
EFIAPI
ScsiReadCapacity16Command (
  IN  EFI_SCSI_IO_PROTOCOL  *ScsiIo,
  IN  UINT64                Timeout,
  IN  VOID                  *SenseData,
  IN OUT UINT8              *SenseDataLength,
  OUT UINT8                 *HostAdapterStatus,
  OUT UINT8                 *TargetStatus,
  OUT VOID                  *DataBuffer,
  IN OUT UINT32             *DataLength,
  IN  BOOLEAN               PMI
  );


/**
  Execute Read(10) SCSI command on a specific SCSI target.

  Executes the SCSI Read(10) command on the SCSI target specified by ScsiIo.
  If Timeout is zero, then this function waits indefinitely for the command to complete.
  If Timeout is greater than zero, then the command is executed and will timeout
  after Timeout 100 ns units.  The StartLba and SectorSize parameters are used to
  construct the CDB for this SCSI command.
  If ScsiIo is NULL, then ASSERT().
  If SenseDataLength is NULL, then ASSERT().
  If HostAdapterStatus is NULL, then ASSERT().
  If TargetStatus is NULL, then ASSERT().
  If DataLength is NULL, then ASSERT().


  @param[in]      ScsiIo               A pointer to SCSI IO protocol.
  @param[in]      Timeout              The length of timeout period.
  @param[in, out] SenseData            A pointer to output sense data.
  @param[in, out] SenseDataLength      The length of output sense data.
  @param[out]     HostAdapterStatus    The status of Host Adapter.
  @param[out]     TargetStatus         The status of the target.
  @param[in, out] DataBuffer           Read 10 command data.
  @param[in, out] DataLength           The length of data buffer.
  @param[in]      StartLba             The start address of LBA.
  @param[in]      SectorSize           The sector size.

  @retval  EFI_SUCCESS          Command is executed successfully.
  @retval  EFI_BAD_BUFFER_SIZE  The SCSI Request Packet was executed, but the entire DataBuffer could
                                not be transferred. The actual number of bytes transferred is returned in DataLength.
  @retval  EFI_NOT_READY        The SCSI Request Packet could not be sent because there are too many 
                                SCSI Command Packets already queued.
  @retval  EFI_DEVICE_ERROR     A device error occurred while attempting to send SCSI Request Packet.
  @retval  EFI_UNSUPPORTED      The command described by the SCSI Request Packet is not supported by 
                                the SCSI initiator(i.e., SCSI  Host Controller)
  @retval  EFI_TIMEOUT          A timeout occurred while waiting for the SCSI Request Packet to execute.

**/
EFI_STATUS
EFIAPI
ScsiRead10Command (
  IN     EFI_SCSI_IO_PROTOCOL  *ScsiIo,
  IN     UINT64                Timeout,
  IN OUT VOID                  *SenseData,   OPTIONAL
  IN OUT UINT8                 *SenseDataLength,
     OUT UINT8                 *HostAdapterStatus,
     OUT UINT8                 *TargetStatus,
  IN OUT VOID                  *DataBuffer,  OPTIONAL
  IN OUT UINT32                *DataLength,
  IN     UINT32                StartLba,
  IN     UINT32                SectorSize
  );


/**
  Execute Write(10) SCSI command on a specific SCSI target.

  Executes the SCSI Write(10) command on the SCSI target specified by ScsiIo.
  If Timeout is zero, then this function waits indefinitely for the command to complete.
  If Timeout is greater than zero, then the command is executed and will timeout after
  Timeout 100 ns units.  The StartLba and SectorSize parameters are used to construct
  the CDB for this SCSI command.
  If ScsiIo is NULL, then ASSERT().
  If SenseDataLength is NULL, then ASSERT().
  If HostAdapterStatus is NULL, then ASSERT().
  If TargetStatus is NULL, then ASSERT().
  If DataLength is NULL, then ASSERT().

  @param[in]      ScsiIo               SCSI IO Protocol to use
  @param[in]      Timeout              The length of timeout period.
  @param[in, out] SenseData            A pointer to output sense data.
  @param[in, out] SenseDataLength      The length of output sense data.
  @param[out]     HostAdapterStatus    The status of Host Adapter.
  @param[out]     TargetStatus         The status of the target.
  @param[in, out] DataBuffer           A pointer to a data buffer.
  @param[in, out] DataLength           The length of data buffer.
  @param[in]      StartLba             The start address of LBA.
  @param[in]      SectorSize           The sector size.

  @retval  EFI_SUCCESS          Command is executed successfully.
  @retval  EFI_BAD_BUFFER_SIZE  The SCSI Request Packet was executed, but the entire DataBuffer could
                                not be transferred. The actual number of bytes transferred is returned in DataLength.
  @retval  EFI_NOT_READY        The SCSI Request Packet could not be sent because there are too many 
                                SCSI Command Packets already queued.
  @retval  EFI_DEVICE_ERROR     A device error occurred while attempting to send SCSI Request Packet.
  @retval  EFI_UNSUPPORTED      The command described by the SCSI Request Packet is not supported by 
                                the SCSI initiator(i.e., SCSI  Host Controller)
  @retval  EFI_TIMEOUT          A timeout occurred while waiting for the SCSI Request Packet to execute.

**/
EFI_STATUS
EFIAPI
ScsiWrite10Command (
  IN     EFI_SCSI_IO_PROTOCOL  *ScsiIo,
  IN     UINT64                Timeout,
  IN OUT VOID                  *SenseData,   OPTIONAL
  IN OUT UINT8                 *SenseDataLength,
     OUT UINT8                 *HostAdapterStatus,
     OUT UINT8                 *TargetStatus,
  IN OUT VOID                  *DataBuffer,  OPTIONAL
  IN OUT UINT32                *DataLength,
  IN     UINT32                StartLba,
  IN     UINT32                SectorSize
  );


#endif
