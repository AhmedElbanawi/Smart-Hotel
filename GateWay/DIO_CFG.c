#include "STD_TYPES.h"
#include "DIO_CFG.h"
DIO_PIN_DIRECTION_t Pin_Direction[DIO_MAX_PINS] = {

		DIO_PIN_DIRECTION_INPUT_FLOAT, 			/* PINA0 */
		DIO_PIN_DIRECTION_INPUT_FLOAT, 			/* PINA1 */
		DIO_PIN_DIRECTION_INPUT_FLOAT, 			/* PINA2 */
		DIO_PIN_DIRECTION_INPUT_FLOAT, 			/* PINA3 */

		DIO_PIN_DIRECTION_OUTPUT, 			/* PINA4 */
		DIO_PIN_DIRECTION_OUTPUT, 			/* PINA5 */
		DIO_PIN_DIRECTION_OUTPUT, 			/* PINA6 */
		DIO_PIN_DIRECTION_OUTPUT, 			/* PINA7 */

		DIO_PIN_DIRECTION_OUTPUT, 			/* PINB0 */
		DIO_PIN_DIRECTION_OUTPUT,			/* PINB1 */
		DIO_PIN_DIRECTION_OUTPUT,			/* PINB2 */
		DIO_PIN_DIRECTION_OUTPUT,			/* PINB3 */
		DIO_PIN_DIRECTION_OUTPUT,			/* PINB4/SS/Master */
		DIO_PIN_DIRECTION_OUTPUT,			/* PINB5/MOSI */
		DIO_PIN_DIRECTION_INPUT_FLOAT,			/* PINB6/MISO */
		DIO_PIN_DIRECTION_OUTPUT,			/* PINB7/CLK */

		DIO_PIN_DIRECTION_OUTPUT, 			/* PINC0 */
		DIO_PIN_DIRECTION_OUTPUT,			/* PINC1 */
		DIO_PIN_DIRECTION_OUTPUT,			/* PINC2 */
		DIO_PIN_DIRECTION_OUTPUT,			/* PINC3 */
		DIO_PIN_DIRECTION_OUTPUT,			/* PINC4 */
		DIO_PIN_DIRECTION_OUTPUT,			/* PINC5 */
		DIO_PIN_DIRECTION_OUTPUT,			/* PINC6 */
		DIO_PIN_DIRECTION_OUTPUT,			/* PINC7 */

		DIO_PIN_DIRECTION_OUTPUT, 			/* PIND0 */
		DIO_PIN_DIRECTION_OUTPUT,			/* PIND1 */
		DIO_PIN_DIRECTION_OUTPUT,			/* PIND2 */
		DIO_PIN_DIRECTION_OUTPUT,			/* PIND3 */
		DIO_PIN_DIRECTION_OUTPUT,			/* PIND4 */
		DIO_PIN_DIRECTION_OUTPUT,			/* PIND5 */
		DIO_PIN_DIRECTION_OUTPUT,			/* PIND6 */
		DIO_PIN_DIRECTION_OUTPUT			/* PIND7 */
};
