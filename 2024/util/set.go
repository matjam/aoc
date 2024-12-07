package util

type Set[T comparable] map[T]bool

func SetOf[T comparable](elems ...T) Set[T] {
	s := make(Set[T])

	for _, elem := range elems {
		s.Add(elem)
	}

	return s
}

func (s Set[T]) Add(elem T) {
	s[elem] = true
}

func (s Set[T]) Remove(elem T) {
	delete(s, elem)
}

func (s Set[T]) Contains(elem T) bool {
	_, ok := s[elem]
	return ok
}

func (universal Set[T]) Not(s Set[T]) Set[T] {
	not := make(Set[T])

	for elem := range universal {
		if !s.Contains(elem) {
			not.Add(elem)
		}
	}

	return not
}

func (left Set[T]) Intersection(right Set[T]) Set[T] {
	new := make(Set[T])

	for elem := range left {
		if right.Contains(elem) {
			new.Add(elem)
		}
	}

	return new
}

func (left Set[T]) Union(right Set[T]) Set[T] {
	new := make(Set[T])

	for elem := range left {
		new.Add(elem)
	}

	for elem := range right {
		new.Add(elem)
	}

	return new
}
