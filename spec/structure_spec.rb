require "./lib/modules/structure"

describe Structure do

	it "creates a new structure usign default location " do
		Structure::create "new app"
		default_location = Pathname.pwd.to_s
		Dir.chdir default_location
		File.exist?("new_app.ino").should be_true 
		File.exist?("new_app.rb").should be_true 
		Dir.exist?("modules").should be_true 
		Dir.exist?("configs").should be_true 

	end

	it "creates a new structure passing a location as parameter " do
		location = Pathname.pwd.to_s
		Structure::create "new app b", location
		Dir.chdir "#{location}/new_app_b"
		File.exist?("new_app_b.ino").should be_true 
		File.exist?("new_app_b.rb").should be_true 
		Dir.exist?("modules").should be_true 
		Dir.exist?("configs").should be_true 

	end

	it "removes the structure using default location " do

	end

	it "removes the structure passing a location as parameter " do

	end

end