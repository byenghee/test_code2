basic design decision like belows
.Item defined as Item object
.Promotion function defined as function object
.Checkout class defined as template with function object class type as type argument
.to minimize item object creation or copy, Checkout class get Item's pointer than
  object itself.
 