#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include "event.h"
#include "type.h"
#include "midi.h"

/**
 * @ingroup MIDI
 * A basic event consisting of an id, a message and arbitary optional
 * data.
 */
struct MIDIEvent {
  int refs;
  size_t id;
  size_t length;
  char * message;
  void * info;
};

/**
 * @brief Declare the @c MIDIEventType type specification.
 */
MIDI_TYPE_SPEC_CODING( MIDIEvent, 0x3010 );

#pragma mark Creation and destruction
/**
 * @name Creation and destruction
 * Creating, destroying and reference counting of MIDIEvent objects.
 * @{
 */

/**
 * @brief Create a MIDIEvent instance.
 * Allocate space and initialize a MIDIEvent instance.
 * @public @memberof MIDIEvent
 * @param id      A (hopefully) unique ID.
 * @param info    Any optional data to be associated with the event.
 * @param message A message format that may contain placeholders.
 * @param ...     The data to be filled into the message format placeholders.
 *                (Refer to the sprintf specification for details.)
 * @return a pointer to the created event structure on success.
 * @return a @c NULL pointer if the event could not created.
 */
struct MIDIEvent * MIDIEventCreate( size_t id, void * info, char * message, ... ) {
  void * buffer;
  size_t length, required;
  va_list vargs;
  struct MIDIEvent * event = malloc( sizeof( struct MIDIEvent ) );
  MIDIPrecondReturn( event != NULL, ENOMEM, NULL );

  event->refs = 1;
  event->id   = id;
  event->info = info;

  if( message != NULL ) {
    length = 64;
    buffer = malloc( length );

    va_start( vargs, message );
    do {
      if( buffer == NULL ) {
        MIDIError( ENOMEM, "Could not allocate space for static buffer." );
        return NULL;
      }
      required = vsnprintf( buffer, length-1, message, vargs );
      if( required > length ) {
        buffer = realloc( buffer, required );
        length = required;
      }
    } while( required > length );
    va_end( vargs );

    event->message = buffer;
    event->length  = length;
  } else {
    event->message = NULL;
    event->length  = 0;
  }

  return event;
}

/**
 * @brief Destroy a MIDIEvent instance.
 * Free all resources occupied by the event and release all referenced objects.
 * @public @memberof MIDIEvent
 * @param event The event.
 */
void MIDIEventDestroy( struct MIDIEvent * event ) {
  MIDIPrecondReturn( event != NULL, EFAULT, (void)0 );
  if( event->message != NULL ) {
    free( event->message );
  }
  free( event );
}

/**
 * @brief Retain a MIDIEvent instance.
 * Increment the reference counter of an event so that it won't be destroyed.
 * @public @memberof MIDIEvent
 * @param event The event.
 */
void MIDIEventRetain( struct MIDIEvent * event ) {
  MIDIPrecondReturn( event != NULL, EFAULT, (void)0 );
  event->refs++;
}

/**
 * @brief Release a MIDIEvent instance.
 * Decrement the reference counter of an event. If the reference count
 * reached zero, destroy the event.
 * @public @memberof MIDIEvent
 * @param event The event.
 */
void MIDIEventRelease( struct MIDIEvent * event ) {
  MIDIPrecondReturn( event != NULL, EFAULT, (void)0 );
  if( ! --event->refs ) {
    MIDIEventDestroy( event );
  }
}

/** @} */

int MIDIEventGetId( struct MIDIEvent * event, size_t * id ) {
  MIDIPrecond( event != NULL, EFAULT );
  MIDIPrecond( id != NULL, EINVAL );
  *id = event->id;
  return 0;
}

int MIDIEventGetInfo( struct MIDIEvent * event, void ** info ) {
  MIDIPrecond( event != NULL, EFAULT );
  MIDIPrecond( info != NULL, EINVAL );
  *info = event->info;
  return 0;
}

int MIDIEventEncode( struct MIDIEvent * event, size_t size, void * buffer, size_t * written ) {
  MIDIPrecond( event != NULL, EFAULT );
  MIDIPrecond( buffer != NULL, EINVAL );
  size_t required = 8 + event->length;
  MIDIPrecond( size >= required, ENOMEM );

  return 0;
}

int MIDIEventDecode( struct MIDIEvent * event, size_t size, void * buffer, size_t * read ) {
  MIDIPrecond( event != NULL, EFAULT );
  MIDIPrecond( buffer != NULL, EINVAL );
  size_t required = 5;
  MIDIPrecond( size >= required, EINVAL );
  
  return 1;
}
