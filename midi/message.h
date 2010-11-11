#ifndef MIDIKIT_MIDI_MESSAGE_H
#define MIDIKIT_MIDI_MESSAGE_H
#include "midi.h"

struct MIDIMessage;

struct MIDIMessage * MIDIMessageCreate( MIDIMessageStatus status );
void MIDIMessageDestroy( struct MIDIMessage * message );
void MIDIMessageRetain( struct MIDIMessage * message );
void MIDIMessageRelease( struct MIDIMessage * message );

int MIDIMessageGetStatus( struct MIDIMessage * message, MIDIMessageStatus * status );
int MIDIMessageSetStatus( struct MIDIMessage * message, MIDIMessageStatus status );
int MIDIMessageGet( struct MIDIMessage * message, MIDIProperty property, size_t size, void * value );
int MIDIMessageSet( struct MIDIMessage * message, MIDIProperty property, size_t size, void * value );

int MIDIMessageRead( struct MIDIMessage * message, size_t bytes, unsigned char * buffer );
int MIDIMessageWrite( struct MIDIMessage * message, size_t bytes, unsigned char * buffer );

#endif