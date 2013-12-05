
puts ClearSilver.class
puts ClearSilver.to_s
puts ClearSilver::HDF

hdf = ClearSilver::HDF.new
hdf.set_value "aaa", "000"
hdf.set_value "bbb", "111"
hdf.set_value "ccc", "222"
hdf.dump

