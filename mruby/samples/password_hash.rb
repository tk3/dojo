def compare_hash_pwd(password, hash_password)
  digest_tbl = {
    "MD5" => Digest::MD5,
    "SHA1" => Digest::SHA1,
    "SHA256" => Digest::SHA256,
    "SHA384" => Digest::SHA384,
    "SHA512" => Digest::SHA512,
    "none" => Proc.new {|s| s},
  }

  if hash_password =~ /^{(.+)}(.+)/
    digest_type = $1
    digest_string = $2
    if digest_tbl.key?(digest_type)
      digest_class = digest_tbl[digest_type]
    end
  end

  return password == hash_password  if digest_class.nil?

  Base64::encode(digest_class.digest(password)).eql?(digest_string)
end

puts compare_hash_pwd("foo", "foo")
puts compare_hash_pwd("foo", "{MD5}rL0Y20zC+Fzt72VPzMSk2A==")
puts compare_hash_pwd("foo", "{SHA1}C+7Hteo/D9vJXQ3UfzxbwnXaijM=")
puts compare_hash_pwd("foo", "{SHA256}LCa0a2j/xo/5m0U8HTBBNBNCLXBkg7+g+YpeiGJm564=")
puts compare_hash_pwd("foo", "{SHA384}mMEf/f3VQGdrGhN8saIrKnA1DJpEFx1rEYDGvly7LuP3nVMsih3Z7y6OCOdSo7q7")
puts compare_hash_pwd("foo", "{SHA512}9/u6bgY2+JDlb7vzKD5STG+jIErimDgtYkdB0NxmODJuKCxBvl5CVNiCB3LFUYosWowMf37aGVlKfrU5RT4e1w==")

puts compare_hash_pwd("bar", "foo")
puts compare_hash_pwd("bar", "{MD5}rL0Y20zC+Fzt72VPzMSk2A==")
puts compare_hash_pwd("bar", "{SHA1}C+7Hteo/D9vJXQ3UfzxbwnXaijM=")
puts compare_hash_pwd("bar", "{SHA256}LCa0a2j/xo/5m0U8HTBBNBNCLXBkg7+g+YpeiGJm564=")
puts compare_hash_pwd("bar", "{SHA384}mMEf/f3VQGdrGhN8saIrKnA1DJpEFx1rEYDGvly7LuP3nVMsih3Z7y6OCOdSo7q7")
puts compare_hash_pwd("bar", "{SHA512}9/u6bgY2+JDlb7vzKD5STG+jIErimDgtYkdB0NxmODJuKCxBvl5CVNiCB3LFUYosWowMf37aGVlKfrU5RT4e1w==")
