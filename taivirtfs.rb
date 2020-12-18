# frozen_string_literal: true

class TaiVirtFS
  def initialize(filename = '/dev/taivirtfs')
    @file = File.open filename, 'r'
  end

  def close
    @file.close
  end

  def inspect_cmd
    s = +''
    @file.ioctl 17_664, s
    s
  end

  def mount(target, source, file_system_type, flags)
    @file.ioctl(
      17_665,
      [
        target,
        source,
        file_system_type,
        flags,
      ].pack('a256a256a256Q'),
    )
  end
end
