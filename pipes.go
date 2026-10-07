package main

import (
	"fmt"
	"math"
)

const (
	sound = 1135.35 * 12 // in/second at 75f

	H      = .5          // universal pipe mouth height
	ALarge = 2.5 * 2.5   // area for large pipes
	ASmall = 1.25 * 1.25 // area for small pipes
	BLarge = 2.5 * H
	BSmall = 1.25 * H
	mouth  = 3.0
	buffer = 2.0
	DLarge = 2.5
	DSmall = 1.25
)

// equal tempered frequencies
//
// http://hyperphysics.phy-astr.gsu.edu/hbase/Music/et.html
var (
	freqs = []float64{
		130.81,
		138.59,
		146.83,
		155.56,
		164.81,
		174.61,
		185.00,
		196.00,
		207.65,
		220.00,
		233.08,
		246.94,
		261.63,
		277.18,
		293.66,
		311.13,
		329.63,
		349.23,
		369.99,
		392.00,
		415.30,
		440.00,
		466.16,
		493.88,
	}
	notes = []string{
		" c3",
		"c♯3",
		" d3",
		"d♯3",
		" e3",
		" f3",
		"f♯3",
		" g3",
		"g♯3",
		" a3",
		"a♯3",
		" b3",
		" c4",
		"c♯4",
		" d4",
		"d♯4",
		" e4",
		" f4",
		"f♯4",
		" g4",
		"g♯4",
		" a4",
		"a♯4",
		" b4",
	}
)

func main() {
	for i := 1; i <= 24; i++ {
		// calculate pipe length
		note := notes[i-1]
		freq := freqs[i-1]

		var A float64
		var B float64
		var D float64
		var DL float64

		if i <= 16 {
			A = ALarge
			B = BLarge
			D = DLarge
		} else {
			A = ASmall
			B = BSmall
			D = DSmall
		}
		DL = D + 0.5

		// open pipe is l = v/2f
		leff := (sound / (2 * freq))

		l := (leff - (.3 * H)) - (.8 * (A / math.Sqrt(B)))

		fmt.Printf("pipe %2d: note: %v, freq: %2.2f, length: %2.2fin, length with mouth and buffer %2.2fin, sides %1.2fin x %1.2fin\n", i, note, freq, l, l+mouth+buffer, D, DL)

	}
}
