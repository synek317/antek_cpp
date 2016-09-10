#!/bin/bash

cat << EOF
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
	<key>animations</key>
	<dict>
EOF

for name in `find ./characters -mindepth 2 -maxdepth 2 -type d`; do
cat << EOF
		<key>${name:13}</key>
		<dict>
			<key>delay</key>
			<real>0.05</real>
			<key>frames</key>
			<array>
EOF
	for file in `find $name -mindepth 1 -maxdepth 1 -type f | sort`; do
		echo "				<string>${file:13}</string>"
	done
cat << EOF
			</array>
		</dict>
EOF
done

cat << EOF
	</dict>
</dict>
</plist>
EOF