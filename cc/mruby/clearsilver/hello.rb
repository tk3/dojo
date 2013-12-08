
puts ClearSilver.class
puts ClearSilver.to_s
puts ClearSilver::HDF

hdf = ClearSilver::HDF.new
hdf.set_value "aaa", "000"
hdf.set_value "bbb", "111"
hdf.set_value "ccc", "222"
hdf.set_value "name", "Administrator"
hdf.dump

cs = ClearSilver::CS.new(hdf)
cs.parse_file("template.cs")
r = cs.render()
puts r

