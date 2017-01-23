<?php

use Illuminate\Database\Seeder;

class rfid extends Seeder
{
    /**
     * Run the database seeds.
     *
     * @return void
     */
    public function run()
    {
    	$faker = Faker\Factory::create();

    	for ($i = 0; $i < 50; $i++)
		{
			DB::table('rfid_cards') -> insert([
				'cardUID' => $faker -> macAddress,
				'isicID' => $faker -> randomNumber(9)
			]);
		}
    }
}
