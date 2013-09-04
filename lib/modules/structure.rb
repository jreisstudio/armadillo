require "pathname"

module Structure

	def self.create  app_name,location=nil
		location = Pathname.pwd.to_s if location == nil
		creation_dir = "#{location}/#{camelize app_name}"
		Dir.mkdir creation_dir
		Dir.chdir creation_dir
		#creates the Project default structure
		Dir.mkdir "modules"
		Dir.mkdir "configs"
		File.new("#{camelize app_name}.ino","w")
		File.new("#{camelize app_name}.rb", "w")
	end

	def self.remove app_name,location=nil



	end

private
	def self.camelize string_to_camelize
		string_to_camelize.downcase!
		string_to_camelize.gsub(" ", '_')  
	end

end