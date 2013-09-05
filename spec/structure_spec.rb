require "./lib/modules/structure"

describe Structure do
	let(:location) {Pathname.pwd.to_s}

	it "creates a new structure usign default location " do	
		Structure::create "new app"
		default_location = "#{location}/new_app"
		Dir.chdir default_location
		File.exist?("new_app.ino").should be_true 
		File.exist?("new_app.rb").should be_true 
		Dir.exist?("modules").should be_true 
		Dir.exist?("configs").should be_true 
		Dir.chdir "#{location}"

	end

	it "creates a new structure passing a location as parameter " do

		Structure::create "new app b", location
		Dir.chdir "#{location}/new_app_b"
		File.exist?("new_app_b.ino").should be_true 
		File.exist?("new_app_b.rb").should be_true 
		Dir.exist?("modules").should be_true 
		Dir.exist?("configs").should be_true 
		Dir.chdir "#{location}"

	end

	it "removes the structure using default location " do
		app_name = "new_app"
		Dir.chdir "#{location}"
		Structure::remove app_name
		puts "#{location}"
		Dir.exist?(app_name).should be_false 

	end

	it "removes the structure passing a location as parameter " do
		location = Pathname.pwd.to_s
		app_name = "new_app_b"
		Structure::remove app_name,location
		Dir.exist?(app_name).should be_false 

	end

end