package util

type Vector struct {
	X, Y int
}

func (v Vector) RotateOrigin90() Vector {
	return Vector{
		X: v.Y,
		Y: -v.X,
	}
}

func (v Vector) Rotate90(about Vector) Vector {
	return v.Sub(about).RotateOrigin90().Add(about)
}

func (left Vector) Add(right Vector) Vector {
	return Vector{
		X: left.X + right.X,
		Y: left.Y + right.Y,
	}
}

func (v Vector) Opposite() Vector {
	return Vector{
		X: -v.X,
		Y: -v.Y,
	}
}

func (left Vector) Sub(right Vector) Vector {
	return Vector{
		X: left.X - right.X,
		Y: left.Y - right.Y,
	}
}
