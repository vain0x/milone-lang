module rec newtype_in_records.Program

// There was an issue that invalid code is emitted
// when a field of records is of newtype variant.

type Day = Day of int

type DayRange = { Start: Day; End: Day }

let newDay (value: int) =
  assert (1 <= value && value <= 31)
  Day value

let dayToInt (Day value) = value

let newDayRange (start: Day) (endDay: Day) : DayRange =
  assert (dayToInt start <= dayToInt endDay)
  { Start = start; End = endDay }

let between (day: Day) (range: DayRange) =
  dayToInt range.Start <= dayToInt day
  && dayToInt day <= dayToInt range.End

let main _ =
  assert (between (newDay 13) (newDayRange (newDay 10) (newDay 20)))
  0
